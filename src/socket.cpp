#include "socket.hpp"

Socket::Socket()
{
#ifndef __LINUX
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 0), &wsa) != 0)
    {
        std::cout << "Couldn't initialize WinSock" << std::endl;
        exit(1);
    }
#endif // __LINUX
    this->sockaddr.sin_family = AF_INET;
}

int Socket::connect(std::string address, size_t port)
{
    this->sockaddr.sin_addr.s_addr = inet_addr(this->resolve(address).c_str());
    this->sockaddr.sin_port = htons(port);

    this->sock = socket(AF_INET, SOCK_STREAM, 0);
    int ret = ::connect(this->sock, (struct sockaddr *)&this->sockaddr, sizeof(sockaddr));

    if(errno == 0)
    {
        this->connection.status = ConnectionStatus::CONNECTION_OK;
        this->connection.host = address;
        this->connection.port = port;
    }

#ifdef __LINUX
    fcntl(this->sock, F_SETFL, O_NONBLOCK); // make this->sock non-blocking
#else
    u_long mode = 1;
    ioctlsocket(this->sock, FIONBIO, &mode);
#endif
    return ret;
}

int Socket::close()
{
#ifdef __LINUX
    return ::close(this->sock);
#else
    return ::closesocket(this->sock);
#endif
    this->connection.status = ConnectionStatus::CONNECTION_DEAD;
}

int Socket::select(SelectMode select_mode, int _timeout)
{
    struct timeval timeout;
    timeout.tv_sec = _timeout;
    timeout.tv_usec = 0;
    fd_set _set;
    FD_ZERO(&_set);
    //FD_SET(0, &_set);
    FD_SET(this->sock, &_set);

    fd_set *read_set = select_mode == SELECT_READ? &_set : NULL;
    fd_set *write_set = select_mode == SELECT_WRITE? &_set : NULL;

    int sel = ::select(this->sock + 1, read_set, write_set, NULL, &timeout);

    if (FD_ISSET(this->sock, select_mode == SELECT_READ? read_set : write_set))
    {
        return 1;
    }
    else if (sel < 0)
    {
        return -1;
    }

    return 0;
}

int Socket::send(std::string str)
{
    int s = this->select(SELECT_WRITE, this->timeout);
    if (s == -1)
    {
        return 0;
    }

    str = str + "\r\n";
    return ::send(this->sock, str.c_str(), str.length(), 0);
}

std::string Socket::recv()
{
    char buf;
    std::string ret;
    int socket_status;

    do
    {
        int s = this->select(SELECT_READ, this->timeout);
        if (s == -1)
        {
            return ret;
        }

        socket_status = ::recv(this->sock, &buf, 1, 0);

        if (socket_status == 1)
        {
            ret += buf;
        }
        else if (socket_status == 0)
        {
            this->connection.status = ConnectionStatus::CONNECTION_DEAD;
            return ret;
        }
        else
        {
            switch (errno)
            {
                case EWOULDBLOCK:
                    return ret;
                break;
                default:
                    this->connection.status = ConnectionStatus::CONNECTION_DEAD;
                    return ret;
                break;
            }
        }
    } while (buf != '\n');

    return ret;
}

std::string Socket::resolve(std::string addr)
{
    hostent *h;
    h = gethostbyname(addr.c_str());

    std::string ret;

    if (h)
    {
        ret = inet_ntoa(*(struct in_addr *)h->h_addr);
    }

    return ret;
}

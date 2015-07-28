#ifndef __SOCKET_HPP_INCLUDED
#define __SOCKET_HPP_INCLUDED

#include <iostream>
#ifdef __LINUX
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#else
#include <winsock2.h>
#endif // __LINUX

class Socket
{
    private:
    sockaddr_in sockaddr;
    static const int timeout = 1;

    protected:
#ifdef __LINUX
    int sock;
#else
    SOCKET sock;
#endif // __LINUX

    public:
    enum ConnectionStatus
    {
        CONNECTION_DEAD = -1,
        CONNECTION_OK
    };

    enum SelectMode
    {
        SELECT_WRITE,
        SELECT_READ
    };

    struct
    {
        enum ConnectionStatus status;
        std::string host;
        size_t port;
    } connection;
    Socket();
    int connect(std::string address, size_t port);
    int close();
    int select(SelectMode select_mode, int _timeout);
    int send(std::string str);
    std::string recv();
    std::string resolve(std::string domain);
};

#endif

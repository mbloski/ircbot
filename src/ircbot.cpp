#include "ircbot.hpp"

IRCBot::IRCBot(std::string _host, size_t _port, std::string _nickname, std::vector<std::string> channels)
{
    this->RegisterHandlers();
    this->ircsocket.connect(_host, _port);
    this->nick = _nickname;
    this->netinfo.host = _host;
    this->netinfo.port = _port;
    this->Nick(this->nick);
    this->Register();

    this->autojoin_channels = channels;
}

IRCBot::~IRCBot()
{
    this->ircsocket.close();
}

void IRCBot::RegisterHandlers()
{
    this->hmn.add(std::vector<std::string>{"ERROR"}, Handler::generic_info, this->hmn.HANDLE_F);
    this->hmn.add("433", Handler::nick_inuse, this->hmn.HANDLE_ID);
    this->hmn.add(std::vector<std::string>{"001", "002"}, Handler::welcome, this->hmn.HANDLE_ID);
    this->hmn.add("PING", Handler::ping, this->hmn.HANDLE_F);
    this->hmn.add("PRIVMSG", Handler::privmsg, this->hmn.HANDLE_ID);
    this->hmn.add("NOTICE", Handler::notice, this->hmn.HANDLE_ID);
    this->hmn.add("JOIN", Handler::join, this->hmn.HANDLE_ID);
    this->hmn.add(std::vector<std::string>{"332", "333"}, Handler::join_topic, this->hmn.HANDLE_ID);
    this->hmn.add("353", Handler::join_names, this->hmn.HANDLE_ID);
    this->hmn.add("PART", Handler::part, this->hmn.HANDLE_ID);
    this->hmn.add("QUIT", Handler::quit, this->hmn.HANDLE_ID);
    this->hmn.add("NICK", Handler::nick_change, this->hmn.HANDLE_ID);
    this->hmn.add("TOPIC", Handler::topic, this->hmn.HANDLE_ID);
}

irc::line_t IRCBot::Process(std::string line)
{
    irc::line_t ret;
    std::string tline = line.substr(0, line.length() - 2);
    std::vector<std::string> chunks = util::tokenize(tline, ' ');

    ret.str = tline;
    ret.f = chunks[0];

    if (ret.f.empty())
    {
        return ret;
    }

    ret.id = chunks[1];

    ret.mask = ret.f.substr(1, -1);
    if (ret.mask.find('!') != std::string::npos && ret.mask.find('@') != std::string::npos)
    {
        /* If ret.mask is an usermask, get ret.nick, ret.ident and ret.host */
        ret.nick = ret.mask.substr(0, ret.mask.find('!'));
        std::string buffer = ret.mask.substr(ret.mask.find('!') + 1, -1);
        ret.mask = buffer;
        ret.ident = buffer.substr(0, buffer.find('@'));
        ret.host = buffer.substr(buffer.find('@') + 1, -1);
    }

    if (chunks.size() >= 3)
    {
        ret.destination = chunks[2];
        if (ret.destination.front() == ':')
        {
            ret.destination = ret.destination.substr(1, -1);
        }

        /* We chop off chunks[0] in case it was an IPv6 address */
        std::string buffer = ret.str.substr(chunks[0].length() + 1, -1);
        /* And finally get the message, if it exists */
        if (buffer.find_first_of(':') != std::string::npos)
        {
            ret.message = buffer.substr(buffer.find_first_of(':') + 1, -1);
        }
    }

    return ret;
}

void IRCBot::Nick(std::string nickname)
{
    this->ircsocket.send("NICK " + nickname);
    this->nick = nickname;
}

void IRCBot::Register()
{
    this->ircsocket.send("USER blo 0 * :Michael");
}

void IRCBot::Pong(std::string str)
{
    this->ircsocket.send("PONG " + str);
}

void IRCBot::Join(std::string channel)
{
    this->ircsocket.send("JOIN " + channel);
}

void IRCBot::Part(std::string channel, std::string part_message)
{
    std::string line = "PART " + channel;
    if (!part_message.empty())
    {
        line += " " + part_message;
    }
    this->ircsocket.send(line);
}

void IRCBot::Quit(std::string quit_message)
{
    std::string line = "QUIT";
    if (!quit_message.empty())
    {
        line += " " + quit_message;
    }
    this->ircsocket.send(line);
}

void IRCBot::Say(std::string destination, std::string message)
{
    this->ircsocket.send("PRIVMSG " + destination + " :" + message);
}

void IRCBot::Notice(std::string destination, std::string message)
{
    this->ircsocket.send("NOTICE " + destination + " :" + message);
}

void IRCBot::Tick()
{
    if (this->ircsocket.connection.status == this->ircsocket.CONNECTION_OK)
    {
        line = this->Process(this->ircsocket.recv());
        if (!line.str.empty())
        {
            std::cout << line.str << std::endl;
            this->hmn.execute(line, this);
        }
    }
}

bool IRCBot::IsAlive() const {
    return this->ircsocket.connection.status != Socket::ConnectionStatus::CONNECTION_DEAD;
}
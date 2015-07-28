#include "handlers.hpp"

void Handler::join(IRCBot *bot)
{
    if (bot->line.nick == bot->nick)
    {
        /* We joined the channel */
        bot->channels[bot->line.destination] = std::unique_ptr<irc::channel_t>(new irc::channel_t);
    }
    else
    {
        irc::user_t user;
        user.nick = bot->line.nick;
        bot->channels[bot->line.destination]->users[bot->line.nick] = user;
    }
    std::cout << "[" + bot->line.destination + "] " + bot->line.nick + " has joined the channel" << std::endl;
}

void Handler::join_topic(IRCBot *bot)
{
    std::vector<std::string> chunks = util::tokenize(bot->line.str, ' ');
    if (bot->line.id == "332")
    {
        std::string channel = chunks[3];
        bot->channels[channel]->topic.str = bot->line.message;
        std::cout << "[" + channel + "] The topic is \"" + bot->line.message + "\"" << std::endl;
    }

    if (bot->line.id == "333")
    {
        std::string channel = chunks[3];
        std::string topic_setter = chunks[4];
        bot->channels[channel]->topic.setter = topic_setter;
        std::cout << "[" + chunks[3] + "] topic set by " << topic_setter << std::endl;
    }
}

void Handler::join_names(IRCBot *bot)
{
    std::vector<std::string> chunks = util::tokenize(bot->line.str, ' ');
    std::string channel = chunks[4];

    std::vector<std::string> names = util::tokenize(bot->line.message, ' ');

    /* Stupid. */
    if (names.back().back() == '\0')
    {
        names.pop_back();
    }

    for (std::string name : names)
    {
        irc::user_t user;
        if (name[0] == irc::MODE_QOP || name[0] == irc::MODE_AOP || name[0] == irc::MODE_OP || name[0] == irc::MODE_HOP || name[0] == irc::MODE_VOP)
        {
            name = name.substr(1, -1);
            user.mode = static_cast<irc::usermode>(name[0]);
            user.nick = name;
        }
        else
        {
            user.nick = name;
        }

        bot->channels[channel]->users[name] = user;
    }
}

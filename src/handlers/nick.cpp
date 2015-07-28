#include "handlers.hpp"

void Handler::nick_inuse(IRCBot *bot)
{
    std::string new_nick = bot->nick + "_";
    std::cout << "Nickname " + bot->nick + " is already in use, trying " << new_nick << std::endl;
    bot->Nick(new_nick);
}

void Handler::nick_change(IRCBot *bot)
{
    std::string old_nick = bot->line.nick;
    std::string new_nick = bot->line.destination;
    if (bot->line.nick == bot->nick && bot->nick != new_nick)
    {
        bot->nick = new_nick;
    }

    for (auto &i : bot->channels)
    {
        std::string channel = i.first;
        if (bot->channels[channel]->users.find(bot->line.nick) != bot->channels[channel]->users.end())
        {
            irc::user_t user = bot->channels[channel]->users[old_nick];
            bot->channels[channel]->users[new_nick] = user;
            bot->channels[channel]->users.erase(old_nick);
        }
    }

    std::cout << bot->line.nick << " is now known as " << new_nick << std::endl;
}

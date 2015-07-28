#include "handlers.hpp"

void Handler::quit(IRCBot *bot)
{
    /* Erase the quitting user from our channels */
    for (auto &i : bot->channels)
    {
        std::string channel = i.first;
        if (bot->channels[channel]->users.find(bot->line.nick) != bot->channels[channel]->users.end())
        {
            bot->channels[channel]->users.erase(bot->line.nick);
        }
    }

    std::string message = bot->line.nick + " has quit";
    if (!bot->line.message.empty())
    {
        message += " (" + bot->line.message + ")";
    }
    std::cout << message << std::endl;
}

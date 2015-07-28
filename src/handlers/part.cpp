#include "handlers.hpp"

void Handler::part(IRCBot *bot)
{
    if (bot->line.nick == bot->nick)
    {
        bot->channels.erase(bot->line.destination);
    }
    else
    {
        bot->channels[bot->line.destination]->users.erase(bot->line.nick);
    }

    std::string message = "[" + bot->line.destination + "] " + bot->line.nick + " has left the channel";
    if (!bot->line.message.empty())
    {
        message += " (" + bot->line.message + ")";
    }
    std::cout << message << std::endl;
}

#include "handlers.hpp"

void Handler::topic(IRCBot *bot)
{
    bot->channels[bot->line.destination]->topic.str = bot->line.message;
    bot->channels[bot->line.destination]->topic.setter = bot->line.nick;
    //bot->channels[bot->line.destination]->topic.time

    std::cout << "[" + bot->line.destination + "] " + bot->line.nick + " has changed the topic to \"" + bot->line.message + "\"" << std::endl;
}

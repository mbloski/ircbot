#include "handlers.hpp"

void Handler::notice(IRCBot *bot)
{
    std::cout << "[" + bot->line.destination + "] -" + bot->line.nick + "- " + bot->line.message << std::endl;
}

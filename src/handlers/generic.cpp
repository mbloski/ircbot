#include "handlers.hpp"

void Handler::generic_info(IRCBot *bot)
{
    if (bot->line.str.find(" :") != std::string::npos)
    {
        std::cout << bot->line.str.substr(bot->line.str.find(" :") + 2, -1) << std::endl;
    }
}

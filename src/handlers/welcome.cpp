#include "handlers.hpp"

void Handler::welcome(IRCBot *bot)
{
    std::cout << bot->line.message << std::endl;
    for (std::string channel : bot->autojoin_channels)
    {
        bot->Join(channel);
    }
}

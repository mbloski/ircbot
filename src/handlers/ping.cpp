#include "handlers.hpp"

void Handler::ping(IRCBot *bot)
{
    std::string pong_str = bot->line.id;
    pong_str = pong_str.substr(1, -1);
    bot->Pong(pong_str);
}

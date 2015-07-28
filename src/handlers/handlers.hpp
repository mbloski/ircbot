#ifndef __HANDLERS_HPP_INCLUDED
#define __HANDLERS_HPP_INCLUDED

#include "../ircbot.hpp"
#include <algorithm>

class IRCBot;

namespace Handler
{
    void nick_inuse(IRCBot *bot);
    void nick_change(IRCBot *bot);
    void welcome(IRCBot *bot);
    void ping(IRCBot *bot);
    void privmsg(IRCBot *bot);
    void notice(IRCBot *bot);
    void topic(IRCBot *bot);
    void join(IRCBot *bot);
    void join_topic(IRCBot *bot);
    void join_names(IRCBot *bot);
    void part(IRCBot *bot);
    void quit(IRCBot *bot);

    void generic_info(IRCBot *bot);
};

#endif

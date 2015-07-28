#ifndef __HANDLERMANAGER_H_INCLUDED
#define __HANDLERMANAGER_H_INCLUDED

#include <map>
#include <stdint.h>
#include <iostream>
#include <string>
#include <memory>
#include "util.hpp"
#include "irc_types.hpp"

class IRCBot;

class HandlerManager
{
    public:
    HandlerManager();

    enum HandlerType
    {
        HANDLE_ID = 1,
        HANDLE_F
    };

    void add(std::string str, void (*handler_ptr)(IRCBot *), HandlerType);
    void add(std::vector<std::string> _handlers, void (*handler_ptr)(IRCBot *), HandlerType = HANDLE_ID);
    void execute(irc::line_t str, IRCBot *bot);

    private:
    std::map<std::string, std::pair<void*, HandlerType> > handlers;
};

#endif

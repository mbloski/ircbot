#ifndef __IRC_TYPES_HPP_INCLUDED
#define __IRC_TYPES_HPP_INCLUDED

#include <string>

namespace irc
{
    enum usermode
    {
        MODE_QOP = '~',
        MODE_AOP = '&',
        MODE_OP = '@',
        MODE_HOP = '%',
        MODE_VOP = '+',
        MODE_NONE
    };

    struct user_t
    {
        std::string nick;
        usermode mode;
        user_t() { this->mode = MODE_NONE; }
    };

    struct channel_t
    {
        struct
        {
            std::string str;
            std::string setter;
            time_t time;
        } topic;

        std::map<std::string, user_t> users;
    };

    struct line_t
    {
        std::string str;
        std::string f;
        std::string id;
        std::string nick;
        std::string ident;
        std::string host;
        std::string mask;
        std::string destination;
        std::string message;
    };
};
#endif

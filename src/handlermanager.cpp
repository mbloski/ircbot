#include "handlermanager.hpp"

HandlerManager::HandlerManager()
{

}

void HandlerManager::add(std::string str, void (*handler_ptr)(IRCBot *), HandlerType htype)
{
    handlers.insert(std::make_pair(str, std::make_pair((void*)handler_ptr, htype)));
}

void HandlerManager::add(std::vector<std::string> _handlers, void (*handler_ptr)(IRCBot *), HandlerType htype)
{
    for (std::string str : _handlers)
    {
        handlers.insert(std::make_pair(str, std::make_pair((void*)handler_ptr, htype)));
    }
}

void HandlerManager::execute(irc::line_t str, IRCBot *bot)
{
    std::string handle_identifier;
    for(std::string i : {str.id, str.f})
    {
        switch (handlers[i].second)
        {
            case HANDLE_ID:
                handle_identifier = str.id;
            break;
            case HANDLE_F:
                handle_identifier = str.f;
            default:

            break;
        }
    }

    void *handler_ptr = handlers[handle_identifier].first;
    if (handler_ptr != nullptr)
    {
        void (*f)(IRCBot*) = (void(*)(IRCBot*))handler_ptr;
        if(f)
        {
            (*f)(bot);
        }
    }
    else
    {
        /* Unhandled line goes here */
        return;
    }
}

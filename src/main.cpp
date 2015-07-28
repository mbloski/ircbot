#include <iostream>
#include <thread>
#include "ircbot.hpp"
#include "util.hpp"

/* This shit is unfinished. Enjoy SEGFAULTs. --blo */

int main()
{
    std::vector<std::shared_ptr<IRCBot>> bots;

    bots.push_back(std::shared_ptr<IRCBot>(new IRCBot("irc.quakenet.org", 6667, "hue", std::vector<std::string> {"#blotest"})));

    while (!bots.empty())
    {
        for (std::vector<std::shared_ptr<IRCBot>>::iterator it = bots.begin(); it < bots.end(); ++it)
        {
            if (!(*it)->IsAlive())
            {
                std::cout << (*it)->nick << " from " << (*it)->netinfo.host << ":" << (*it)->netinfo.port << " has disconnected." << std::endl;
                bots.erase(it); // TODO: attempt to reconnect if desired?
                continue;
            }
            else
            {
                (*it)->Tick();
            }
        }
    }
    return 0;
}

#include <iostream>
#include <thread>
#include "ircbot.hpp"
#include "util.hpp"

/* This shit is unfinished. Enjoy SEGFAULTs. --blo */

int main()
{
    std::vector<std::shared_ptr<IRCBot>> bots;

    bots.push_back(std::shared_ptr<IRCBot>(new IRCBot("irc.quakenet.org", 6667, "hue", std::vector<std::string>{"#blotest"})));

    while (true)
    {
        for (std::shared_ptr<IRCBot> bot : bots)
        {
            bot->Tick();
        }
    }
    return 0;
}

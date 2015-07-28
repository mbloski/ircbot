#include "handlers.hpp"

void Handler::privmsg(IRCBot *bot)
{
    if (bot->line.message.front() == '\1' && bot->line.message.back() == '\1')
    {
        std::vector<std::string> chunks = util::tokenize(bot->line.message, ' ');
        std::string action = chunks[0].substr(1, -1);
        if (action == "ACTION")
        {
            std::string message = bot->line.message.substr(action.length() + 2, -1);
            message = message.substr(0, message.length() - 1);
            std::cout << "[" + bot->line.destination + "] *" + bot->line.nick + " " + message << std::endl;
        }
        return;
    }
    
    std::cout << "[" + bot->line.destination + "] <" + bot->line.nick + "> " + bot->line.message << std::endl;
    if (bot->line.nick == "blo" && bot->line.message.substr(0, 1) == ".")
    {
        std::vector<std::string> command_argv = util::tokenize(bot->line.message.substr(1, -1), ' ');
        std::string command = command_argv[0];
        std::transform(command.begin(), command.end(), command.begin(), ::toupper);
        std::string command_message = bot->line.message.substr(command_argv[0].length() + 1, -1);
        if (!command_message.empty())
        {
            command_message = command_message.substr(1, -1);
        }

        if (command == "SAY")
        {
            bot->Say(bot->line.destination, command_message);
        }
        else if (command == "NOTICE")
        {
            bot->Notice(command_argv[1], command_message);
        }
        else if (command == "JOIN")
        {
            bot->Join(command_argv[1]);
        }
        else if (command == "PART")
        {
            bot->Part(command_argv[1]);
        }
        else if (command == "NICK")
        {
            bot->Nick(command_argv[1]);
        }
        else if (command == "USERS")
        {
            if (bot->channels[command_argv[1]] == nullptr)
            {
                bot->Say(bot->line.destination, "Sorry, I'm not on the channel \"" + command_argv[1] + "\"");
                return;
            }

            std::string isare = bot->channels[command_argv[1]]->users.size() == 1? "is" : "are";
            std::string userusers = bot->channels[command_argv[1]]->users.size() == 1? "user" : "users";

            std::string ret = "There " + isare + " " + util::to_string(bot->channels[command_argv[1]]->users.size()) + " " + userusers + " on the channel: ";
            std::vector<std::string> names;
            for (auto n : bot->channels[command_argv[1]]->users)
            {
                names.push_back(n.first);
            }
            ret += util::join(names, ", ");
            bot->Say(bot->line.destination, ret);
        }
        else if (command == "QUIT")
        {
            bot->Quit(command_message);
        }
#ifdef DEBUG
        else
        {
            bot->Say(bot->line.destination, "Unrecognized command \"" + command + "\".");
            bot->Say(bot->line.destination, "command_message = \"" + command_message + "\"");
        }
#endif
    }
}

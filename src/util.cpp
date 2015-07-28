#include "util.hpp"

std::vector<std::string> util::tokenize(std::string str, char delimeter)
{
    std::vector<std::string> ret;
    std::string buffer;
    for (unsigned int i = 0; i < str.length(); ++i)
    {
        while (str[i] == delimeter)
        {
            if (!buffer.empty())
            {
                ret.push_back(buffer);
            }
            buffer.clear();
            ++i;
        }
        buffer += str[i];
    }
    ret.push_back(buffer); // push the last element remaining in buffer
    return ret;
}

std::string util::join(std::vector<std::string> vec, std::string glue)
{
    std::string ret;
    for (std::string i : vec)
    {
        ret += i + glue;
    }

    return ret.substr(0, ret.length() - glue.length());
}

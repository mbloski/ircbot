#ifndef __UTIL_HPP_INCLUDED
#define __UTIL_HPP_INCLUDED

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <map>

namespace util
{
    template<typename T> std::string to_string(const T& n)
    {
        std::ostringstream s;
        s << n;
        return s.str();
    }

    std::vector<std::string> tokenize(std::string str, char delimeter);
    std::string join(std::vector<std::string> vec, std::string glue);
};

#endif

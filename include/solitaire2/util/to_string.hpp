#ifndef SOLITAIRE2_UTIL_TOSTRING_HPP
#define SOLITAIRE2_UTIL_TOSTRING_HPP

#include <string>

namespace solitaire2 {

    template <typename T>
    std::string to_string(const T& obj) {
        std::ostringstream ss;
        ss << obj;
        return ss.str();
    }
};

#endif
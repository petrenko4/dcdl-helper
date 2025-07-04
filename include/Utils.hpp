#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <unordered_set>
#include <unordered_map>

namespace Utils {
    extern std::unordered_map<char, int> max_letter_occ;

    std::string trim(const std::string &str);
}

#endif

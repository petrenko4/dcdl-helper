#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <unordered_set>
#include <string>

class Dictionary {
public:
    static std::unordered_set<std::string> load(const std::string &filename);

    static bool isValidWord(const std::string &word, const std::unordered_set<std::string> &dictionary);
};

#endif 

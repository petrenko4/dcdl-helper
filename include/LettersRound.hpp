#ifndef LETTERSROUND_HPP
#define LETTERSROUND_HPP

#include <vector>
#include <string>
#include <unordered_set>

class LettersRound {
public:
    static void generateWords(const std::string &letters,
                              const std::unordered_set<std::string> &dictionary,
                              std::vector<std::string> &validWords);

    static void sortWords(std::vector<std::string> &validWords);
};

#endif 

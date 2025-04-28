#include "LettersRound.hpp"
#include "Dictionary.hpp"
#include <algorithm>
#include <iostream>

void LettersRound::generateWords(const std::string &letters,
                                 const std::unordered_set<std::string> &dictionary,
                                 std::vector<std::string> &validWords) {
    std::string lettersCopy = letters;
    std::sort(lettersCopy.begin(), lettersCopy.end());

    do {
        for (size_t i = 1; i <= lettersCopy.size(); i++) {
            std::string word = lettersCopy.substr(0, i);
            if (Dictionary::isValidWord(word, dictionary)) {
                validWords.push_back(word);
            }
        }
    } while (std::next_permutation(lettersCopy.begin(), lettersCopy.end()));
}

void LettersRound::sortWords(std::vector<std::string> &validWords) {
    std::sort(validWords.begin(), validWords.end(), [](const std::string &a, const std::string &b) {
        return a.length() > b.length();
    });
}

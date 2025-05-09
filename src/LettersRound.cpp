#include "LettersRound.hpp"
#include "Dictionary.hpp"
#include "Utils.hpp"
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <set>

#define MAXLENGTH 45

void LettersRound::generateWords(const std::string &letters,
                                 const std::unordered_set<std::string> &dictionary,
                                 std::vector<std::string> &validWords) {
    std::unordered_map<char, int> available;
    for (char c : letters) {
        ++available[c];
    }

    for (const std::string &word : dictionary) {
        if (word.length() > MAXLENGTH) continue;

        std::unordered_map<char, int> needed;
        bool canForm = true;

        for (char c : word) {
            ++needed[c];
            if (needed[c] > available[c]) {
                canForm = false;
                break;
            }
        }

        if (canForm) {
            validWords.push_back(word);
        }
    }
}


void LettersRound::sortWords(std::vector<std::string> &validWords) {
    std::sort(validWords.begin(), validWords.end(), [](const std::string &a, const std::string &b) {
        return a.length() > b.length();
    });
}

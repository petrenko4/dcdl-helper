#include <iostream>
#include <vector>
#include "../include/Dictionary.hpp"
#include "../include/LettersRound.hpp"
#include "../include/Utils.hpp"
#include <unistd.h>
#include <chrono>
#include <thread>

int main() {
    std::unordered_set<std::string> dictionary = Dictionary::load("../../../data/words.txt");
    // for(auto word: dictionary) {
    //     std::this_thread::sleep_for(std::chrono::milliseconds(1));
    //     std::cout << word << std::endl;
    // }

    int numLetters;
    std::cout << "Enter the number of letters: ";
    std::cin >> numLetters;

    std::string letters;
    std::cout << "Enter the letters: ";
    std::cin >> letters;

    letters = Utils::trim(letters);

    std::vector<std::string> validWords;
    LettersRound::generateWords(letters, dictionary, validWords);

    LettersRound::sortWords(validWords);

    int topN = std::min(10, static_cast<int>(validWords.size()));
    std::cout << "Top " << topN << " largest words:" << std::endl;
    for (int i = 0; i < topN; ++i) {
        std::cout << validWords[i] << std::endl;
    }

    return 0;
}

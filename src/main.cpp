#include <iostream>
#include <vector>
#include "Dictionary.hpp"
#include "LettersRound.hpp"
#include "Utils.hpp"
#include <unistd.h>
#include <chrono>
#include <sstream>
#include <thread>

int main() {
    std::unordered_set<std::string> dictionary = Dictionary::load("../../../data/words.txt");

    //Utils::precompute(dictionary);
    
    std::string letters;
    std::cout << "Enter the letters: ";
    std::cin >> letters;
    letters = Utils::trim(letters);

    std::vector<std::string> validWords;
    LettersRound::generateWords(letters, dictionary, validWords);
    LettersRound::sortWords(validWords);

    int totalWords = static_cast<int>(validWords.size());
    if (totalWords == 0) {
        std::cout << "No valid words found." << std::endl;
        return 0;
    }

    std::cout << totalWords << " valid words found. Use commands to explore them." << std::endl;
    std::cout << "Available commands:\n  next N\n  range A B\n  exit\n" << std::endl;

    int currentIndex = 0;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // clear input buffer

    while (true) {
        std::cout << "> ";
        std::string commandLine;
        std::getline(std::cin, commandLine);
        std::istringstream iss(commandLine);
        std::string command;
        iss >> command;

        if (command == "exit") {
            break;
        } else if (command == "next") {
            int count;
            if (!(iss >> count) || count <= 0) {
                std::cout << "Invalid number." << std::endl;
                continue;
            }

            if (currentIndex >= totalWords) {
                std::cout << "No more words to display." << std::endl;
                continue;
            }

            int endIndex = std::min(currentIndex + count, totalWords);
            for (int i = currentIndex; i < endIndex; ++i) {
                std::cout << (i + 1) << ". " << validWords[i] << " (" << validWords[i].length() << ")" << std::endl;
            }
            currentIndex = endIndex;

        } else if (command == "range") {
            int start, end;
            if (!(iss >> start >> end) || start <= 0 || end <= 0 || start > end || end > totalWords) {
                std::cout << "Invalid range. Must be between 1 and " << totalWords << "." << std::endl;
                continue;
            }

            for (int i = start - 1; i < end; ++i) {
                std::cout << (i + 1) << ". " << validWords[i] << " (" << validWords[i].length() << ")" << std::endl;
            }

        } else {
            std::cout << "Unknown command. Use 'next N', 'range A B', or 'exit'." << std::endl;
        }
    }

    std::cout << "Goodbye!" << std::endl;
    return 0;
}

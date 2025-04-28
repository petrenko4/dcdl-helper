#include "Dictionary.hpp"
#include <fstream>
#include <iostream>

std::unordered_set<std::string> Dictionary::load(const std::string &filename) {
    std::unordered_set<std::string> dictionary;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error opening dictionary file: " << filename << std::endl;
        return dictionary;
    }
    
    std::string word;
    while (file >> word) {
        dictionary.insert(word);
        //std::cout << "word inserted: " << word << std::endl;
    }
    return dictionary;
}

bool Dictionary::isValidWord(const std::string &word, const std::unordered_set<std::string> &dictionary) {
    return dictionary.find(word) != dictionary.end();
}

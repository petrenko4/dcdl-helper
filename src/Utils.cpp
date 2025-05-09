#include "Utils.hpp"
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <fstream>


namespace Utils {

    std::unordered_map<char, int> max_letter_occ;

    std::string trim(const std::string& str) {
        std::string trimmed = str;
        trimmed.erase(trimmed.begin(), std::find_if(trimmed.begin(), trimmed.end(), [](unsigned char ch) {
            return !std::isspace(ch);
            }));
        trimmed.erase(std::find_if(trimmed.rbegin(), trimmed.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
            }).base(), trimmed.end());
        return trimmed;
    }

//     void precompute(std::unordered_set<std::string>& dictionary) {
//         std::unordered_set<char> letters = {
//             'a','b','c','d','e','f','g','h','i','j','k','l','m',
//             'n','o','p','q','r','s','t','u','v','w','x','y','z',
//             '-', '\'', '.', ','
//         };
//         for (char n = '0'; n <= '9'; n++) {
//             max_letter_occ[n] = 2;
//         }
//         for (char c : letters) {
//             for (auto word : dictionary) {
//                 int count = 0;
//                 for (char letter : word) {
//                     if (letter == c) count++;
//                 }
//                 if (max_letter_occ[c] < count) max_letter_occ[c] = count;
//             }
//         }
//     }

//     void load_constraints(const std::string& path) {
//         std::ifstream file(path);
//         if (!file) {
//             std::cerr << "Failed to open constraints file: " << path << std::endl;
//             return;
//         }

//         char letter;
//         int count;
//         while (file >> letter >> count) {
//             max_letter_occ[letter] = count;
//         }
//     }

//     int constraint(char c) {
//         auto it = max_letter_occ.find(c);
//         return (it != max_letter_occ.end()) ? it->second : 0;
//     }
}

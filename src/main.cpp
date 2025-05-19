#include <iostream>
#include <vector>
#include <unordered_set>
#include <limits>
#include <sstream>
#include <unistd.h>
#include <chrono>
#include <thread>
#include "Dictionary.hpp"
#include "LettersRound.hpp"
#include "Utils.hpp"
#include "NumbersRound.hpp"
#include "exprtk.hpp"
#include <optional>

void runLettersRound(const std::unordered_set<std::string>& dictionary) {
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
        return;
    }

    std::cout << totalWords << " valid words found. Use commands to explore them." << std::endl;
    std::cout << "Available commands:\n  next N\n  prev N\n  range A B\n  back\n  exit\n" << std::endl;

    int currentIndex = 0;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true) {
        std::cout << "> ";
        std::string commandLine;
        std::getline(std::cin, commandLine);
        std::istringstream iss(commandLine);
        std::string command;
        iss >> command;

        if (command == "exit" || command == "back") {
            break;
        }
        else if (command == "next") {
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

        }
        else if (command == "prev") {
            int count;
            if (!(iss >> count) || count <= 0) {
                std::cout << "Invalid number." << std::endl;
                continue;
            }
            currentIndex = std::max(0, currentIndex - count);
            int endIndex = std::min(currentIndex + count, totalWords);
            for (int i = currentIndex; i < endIndex; ++i) {
                std::cout << (i + 1) << ". " << validWords[i] << " (" << validWords[i].length() << ")" << std::endl;
            }
            currentIndex = endIndex;

        }
        else if (command == "range") {
            int start, end;
            if (!(iss >> start >> end) || start <= 0 || end <= 0 || start > end || end > totalWords) {
                std::cout << "Invalid range. Must be between 1 and " << totalWords << "." << std::endl;
                continue;
            }

            for (int i = start - 1; i < end; ++i) {
                std::cout << (i + 1) << ". " << validWords[i] << " (" << validWords[i].length() << ")" << std::endl;
            }

        }
        else {
            std::cout << "Unknown command. Use 'next N', 'prev N', 'range A B', 'back', or 'exit'." << std::endl;
        }
    }
}

void runNumbersRound() {

    NumbersRound::initDefaultOperations();

    std::cout << "Available operations:\n";
    for (const auto& [name, _] : NumbersRound::getOperations()) {
        std::cout << "  - " << name << "\n";
    }

    std::cout << "\nCommands:\n"
        << "  'solve' - Solve a numbers round\n"
        << "  'addop' - Add custom operation (ExprTk expression using x and y)\n"
        << "  'back'  - Return to main menu\n"
        << "  'exit'  - Quit the program\n"
        << "  'listop' - List available operations\n";
    while (true) {
        std::cout << "> ";
        std::string command;
        std::getline(std::cin, command);

        if (command.empty()) {
            std::cout << std::endl;
            continue; 
        }

        if (command == "back") {
            break;
        }
        else if (command == "exit") {
            exit(0);
        }
        else if (command == "addop") {
            std::cout << "Enter name for operation: ";
            std::string opname;
            std::getline(std::cin, opname);
            opname = " " + opname + " ";

            std::cout << "Enter expression using x and y (e.g., x*x + y): ";
            std::string expression_str;
            std::getline(std::cin, expression_str);

            using Expr = exprtk::expression<double>;
            using Parser = exprtk::parser<double>;

            double x, y;
            exprtk::symbol_table<double> symbol_table;
            symbol_table.add_variable("x", x);
            symbol_table.add_variable("y", y);
            symbol_table.add_constants();

            Expr expression;
            expression.register_symbol_table(symbol_table);

            Parser parser;
            if (!parser.compile(expression_str, expression)) {
                std::cerr << "Failed to compile expression: " << expression_str << std::endl;
                continue;
            }

            NumbersRound::Operation op = [expression, &x, &y](int a, int b) mutable -> int {
                x = static_cast<double>(a);
                y = static_cast<double>(b);
                return static_cast<int>(expression.value());
                };

            NumbersRound::addCustomOperation(opname, op);
            std::cout << "Added custom operation '" << opname << "'\n";
        }
        else if (command == "solve") {
            std::vector<int> numbers;
            std::cout << "Enter numbers separated by space: ";
            std::string line;
            std::getline(std::cin >> std::ws, line);
            std::istringstream iss(line);
            int n;
            while (iss >> n) {
                numbers.push_back(n);
            }
            if(numbers.size() > 6) {
                std::cout << "Too many numbers. Please enter up to 6 numbers." << std::endl;
                continue;
            }
            int target;
            std::cout << "Enter the target number: ";
            std::cin >> target;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            NumbersRound::printSolutions(NumbersRound::solve(numbers, target));
        }
        else if (command == "listop") {
            const auto& ops = NumbersRound::getOperations();
            if (ops.empty()) {
                std::cout << "No operations defined.\n";
            }
            else {
                std::cout << "Current operations:\n";
                for (const auto& [name, _] : ops) {
                    std::cout << "  - " << name << "\n";
                }
            }
        }

        else {
            std::cout << "Unknown command.\n";
        }
    }
}

int main() {
    std::unordered_set<std::string> dictionary = Dictionary::load("../../data/words.txt");

    while (true) {
        std::cout << "\nChoose a round to play:\n  1. Letters Round\n  2. Numbers Round\n  3. Exit\n> ";
        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "Invalid option." << std::endl;
            continue;
        }

        if (choice == 1) {
            runLettersRound(dictionary);
        }
        else if (choice == 2) {
            runNumbersRound();
        }
        else if (choice == 3) {
            break;
        }
        else {
            std::cout << "Invalid option." << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            continue;
        }
    }

    std::cout << "Goodbye!" << std::endl;
    return 0;
}

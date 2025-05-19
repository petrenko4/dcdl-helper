#ifndef NUMBERSROUND_HPP
#define NUMBERSROUND_HPP

#include <vector>
#include <string>
#include <functional>
#include <unordered_map>
#include <optional>

class NumbersRound {
public:
    using Operation = std::function<std::optional<int>(int, int)>;

    struct Solution {
        int result;
        std::vector<std::string> steps;

        bool operator<(const Solution& other) const {
            if (result != other.result)
                return result < other.result;
            if (steps.size() != other.steps.size())
                return steps.size() < other.steps.size();
            return steps < other.steps;
        }
    };

    struct OperationDef {
        std::string name;
        Operation func;
    };

    static std::vector<Solution> solve(std::vector<int> numbers, int target);
    static void printSolutions(const std::vector<Solution>& solutions);
    static void addCustomOperation(const std::string& name, Operation func);
    static std::vector<OperationDef> getOperations();
    static void initDefaultOperations();

private:
    static std::vector<OperationDef> operations;
};

#endif // NUMBERSROUND_HPP;

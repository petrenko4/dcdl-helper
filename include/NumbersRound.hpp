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
    
    struct OperationDef {
        std::string name;
        Operation func;
    };

    static void solve(std::vector<int> numbers, int target);
    static void addCustomOperation(const std::string& name, Operation func);

private:
    static std::vector<OperationDef> operations;
    static void initDefaultOperations();
};

#endif // NUMBERSROUND_HPP

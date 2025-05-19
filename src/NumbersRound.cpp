#include "NumbersRound.hpp"
#include <iostream>
#include <cmath>
#include <limits>
#include <set>
#include <sstream>
#include <queue>
#include <optional>
#include "exprtk.hpp"

std::vector<NumbersRound::OperationDef> NumbersRound::operations;

void NumbersRound::initDefaultOperations() {
    if (!operations.empty()) return;

    operations = {
        {" + ", [](int a, int b) { return a + b; }},
        {" - ", [](int a, int b) { return a - b; }},
        {" * ", [](int a, int b) { return a * b; }},
        {" / ", [](int a, int b) -> std::optional<int> {
            return (b != 0 && a % b == 0) ? std::optional<int>(a / b) : std::nullopt;
        }}
    };
}

void NumbersRound::addCustomOperation(const std::string& name, Operation func) {
    operations.push_back({ name, func });
}

std::vector<NumbersRound::OperationDef> NumbersRound::getOperations() {
    std::vector<OperationDef> ops;
    for (const auto& op : operations) {
        ops.push_back(op);
    }
    return ops;
}

std::vector<NumbersRound::Solution> NumbersRound::solve(std::vector<int> numbers, int target) {

    struct State {
        int result;
        std::vector<std::string> steps;
    };

    constexpr size_t MAX_SOLUTIONS = 100;

    auto comp = [&](const State& a, const State& b) {
        int da = std::abs(a.result - target);
        int db = std::abs(b.result - target);
        if (da != db) return da < db; 
        if (a.steps.size() != b.steps.size()) return a.steps.size() < b.steps.size(); 
        return a.steps < b.steps; 
        };

    std::set<State, decltype(comp)> solutions(comp);
    std::set<std::string> seen;

    std::function<void(std::vector<int>, std::vector<std::string>)> recurse;
    recurse = [&](std::vector<int> current, std::vector<std::string> steps) {
        for (int val : current) {
                State candidate{ val, steps };

                if (solutions.size() < MAX_SOLUTIONS) {
                    solutions.insert(candidate);
                }
                else {
                    auto worst = std::prev(solutions.end());
                    if (comp(candidate, *worst)) {
                        solutions.erase(worst);
                        solutions.insert(candidate);
                    }
            }
        }

        for (size_t i = 0; i < current.size(); ++i) {
            for (size_t j = 0; j < current.size(); ++j) {
                if (i == j) continue;

                int a = current[i], b = current[j];
                std::vector<int> remaining;
                for (size_t k = 0; k < current.size(); ++k) {
                    if (k != i && k != j)
                        remaining.push_back(current[k]);
                }

                for (const auto& op : operations) {
                    auto resOpt = op.func(a, b);
                    if (!resOpt.has_value()) continue;

                    int res = resOpt.value();
                    std::ostringstream oss;
                    oss << a << op.name << b << " = " << res;

                    std::vector<int> next = remaining;
                    next.push_back(res);
                    std::vector<std::string> nextSteps = steps;
                    nextSteps.push_back(oss.str());

                    std::string key = std::to_string(res) + ":" + std::to_string(next.size()) + ":" + oss.str();
                    if (seen.count(key)) continue;
                    seen.insert(key);

                    recurse(next, nextSteps);
                }
            }
        }
        };

    recurse(numbers, {});

    std::vector<Solution> results;
    for (const auto& state : solutions) {
        results.push_back(Solution{ state.result, state.steps });
    }

    return results;
}

void NumbersRound::printSolutions(const std::vector<NumbersRound::Solution>& solutions) {
    if (solutions.empty()) {
        std::cout << "No solutions found.\n";
        return;
    }

    std::cout << "Best solutions (closest results to target):\n\n";

    int count = 1;
    for (const auto& state : solutions) {
        std::cout << count++ << ") Result: " << state.result << "\n";
        for (size_t i = 0; i < state.steps.size(); ++i) {
            std::cout << "   " << (i + 1) << ". " << state.steps[i] << "\n";
        }
        std::cout << "\n";
    }
}

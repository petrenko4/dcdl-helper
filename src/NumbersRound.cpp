#include "NumbersRound.hpp"
#include <iostream>
#include <cmath>
#include <limits>
#include <set>
#include <sstream>
#include <optional>
#include "exprtk.hpp"

std::vector<NumbersRound::OperationDef> NumbersRound::operations;

void NumbersRound::initDefaultOperations() {
    // Avoid re-initializing the operations if they're already initialized
    if (!operations.empty()) return;

    // Define the default operations
    operations = {
        {" + ", [](int a, int b) { return a + b; }},
        {" - ", [](int a, int b) { return a - b; }},
        {" * ", [](int a, int b) { return a * b; }},
        {" / ", [](int a, int b) -> std::optional<int> {
            return (b != 0 && a % b == 0) ? std::optional<int>(a / b) : std::nullopt;
        }},
        {" % ", [](int a, int b) -> std::optional<int> {
            return (b != 0) ? std::optional<int>(a % b) : std::nullopt;
        }},
        {" ^ ", [](int a, int b) { return a ^ b; }},
        {" pow ", [](int a, int b) -> std::optional<int> {
            if (b < 0 || (a == 0 && b == 0)) return std::nullopt;
            try {
                int res = static_cast<int>(std::pow(a, b));
                return res;
            } catch (...) {
                return std::nullopt;
            }
        }},
    };
}

void NumbersRound::addCustomOperation(const std::string& name, Operation func) {
    // Add the custom operation to the existing list
    operations.push_back({name, func});
}

void NumbersRound::solve(std::vector<int> numbers, int target) {
    initDefaultOperations();  // Ensure default operations are initialized

    struct State {
        std::vector<int> nums;
        std::vector<std::string> steps;
    };

    std::set<std::string> seen;
    State best;
    int bestDiff = std::numeric_limits<int>::max();

    std::function<void(std::vector<int>, std::vector<std::string>)> recurse;
    recurse = [&](std::vector<int> current, std::vector<std::string> steps) {
        if (current.size() == 1) {
            int result = current[0];
            int diff = std::abs(result - target);
            if (diff < bestDiff) {
                bestDiff = diff;
                best.nums = current;
                best.steps = steps;
                if (diff == 0) return;
            }
            return;
        }

        for (size_t i = 0; i < current.size(); ++i) {
            for (size_t j = 0; j < current.size(); ++j) {
                if (i == j) continue;

                int a = current[i], b = current[j];

                std::vector<int> remaining;
                for (size_t k = 0; k < current.size(); ++k)
                    if (k != i && k != j)
                        remaining.push_back(current[k]);

                for (const auto& op : operations) {
                    auto resOpt = op.func(a, b);
                    if (!resOpt.has_value()) continue;

                    int res = resOpt.value();
                    std::ostringstream oss;
                    oss << a << op.name << b << " = " << res;

                    auto next = remaining;
                    next.push_back(res);
                    auto nextSteps = steps;
                    nextSteps.push_back(oss.str());

                    std::string key = std::to_string(res) + ":" + std::to_string(next.size());
                    if (seen.count(key)) continue;
                    seen.insert(key);

                    recurse(next, nextSteps);
                }
            }
        }
    };

    recurse(numbers, {});

    std::cout << "Closest result: " << best.nums[0] << "\nSteps:\n";
    for (size_t i = 0; i < best.steps.size(); ++i)
        std::cout << (i + 1) << ") " << best.steps[i] << "\n";
}

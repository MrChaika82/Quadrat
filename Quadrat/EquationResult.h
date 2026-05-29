#pragma once

#include <vector>
#include <string>

enum class ResultType {
    OK,
    INF,
    WRONG,
    NO_SOLUTION
};

struct EquationResult {
    ResultType type;
    std::vector<std::string> roots;
};
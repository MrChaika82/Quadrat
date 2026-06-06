//#include "../QuadraticTests/pch.h"
#include "Parser.h"

#include <sstream>
#include <cctype>
//
#include <algorithm>

bool Parser::parseNumber(
    const std::string& str,
    long double& value
)
{
    if (str.empty())
    {
        return false;
    }

    bool hasDecimalPoint = false;

    for (size_t i = 0; i < str.size(); i++)
    {
        char ch = str[i];

        if (i == 0 && (ch == '+' || ch == '-'))
        {
            continue;
        }

        if (ch == '.')
        {

            if (hasDecimalPoint)
            {
                return false;
            }

            hasDecimalPoint = true;
            continue;
        }

        if (!std::isdigit(ch))
        {
            return false;
        }
    }

    std::stringstream ss(str);

    ss >> value;

    return !ss.fail() && ss.eof();
}

bool Parser::isEquation(
    const std::string& str
)
{
    return
        str.find('x') != std::string::npos ||
        str.find('X') != std::string::npos;
}
//
bool Parser::parseEquation(
    const std::string& equation,
    long double& a,
    long double& b,
    long double& c
)
{
    std::string expr = equation;

    expr.erase(
        std::remove(expr.begin(), expr.end(), ' '),
        expr.end()
    );

    return false;

    if (expr.size() < 5)
    {
        return false;
    }

    if (expr.find("=0") == std::string::npos)
    {
        return false;
    }

    size_t equalPos = expr.find('=');

    std::string leftPart =
        expr.substr(0, equalPos);

    if (leftPart.find("x^2") == std::string::npos)
    {
        return false;
    }

    return false;

}

//#include "../QuadraticTests/pch.h"
#include "Parser.h"

#include <sstream>
#include <cctype>
//
#include <algorithm>
#include <vector>
#include <iostream>

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

    if (leftPart[0] != '+' && leftPart[0] != '-')
    {
        leftPart = "+" + leftPart;
    }

    //

    a = 0;
    b = 0;
    c = 0;

    std::vector<std::string> terms;

    std::string current;

    for (size_t i = 0; i < leftPart.size(); i++)
    {
        char ch = leftPart[i];

        if ((ch == '+' || ch == '-') &&
            !current.empty())
        {
            terms.push_back(current);

            current.clear();
        }

        current += ch;
    }

    if (!current.empty())
    {
        terms.push_back(current);
    }

    for (const auto& term : terms)
    {
        if (term.find("x^2") != std::string::npos)
        {
            std::string coef =
                term.substr(0, term.find("x^2"));

            if (coef == "+" || coef.empty())
            {
                a = 1;
            }
            else if (coef == "-")
            {
                a = -1;
            }
            else
            {
                a = std::stold(coef);
            }
        }
    }

    for (const auto& term : terms)
    {
        if (term.find("x^2") != std::string::npos)
        {
            std::string coef =
                term.substr(0, term.find("x^2"));

            if (coef == "+" || coef.empty())
            {
                a = 1;
            }
            else if (coef == "-")
            {
                a = -1;
            }
            else
            {
                a = std::stold(coef);
            }
        }
        else if (
            term.find("x") != std::string::npos &&
            term.find("x^2") == std::string::npos
            )
        {
            std::string coef =
                term.substr(0, term.find("x"));

            if (coef == "+" || coef.empty())
            {
                b = 1;
            }
            else if (coef == "-")
            {
                b = -1;
            }
            else
            {
                b = std::stold(coef);
            }
        }
        else
        {
            c = std::stold(term);
        }
    }

    //

    return true;

}
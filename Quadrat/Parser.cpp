//#include "../QuadraticTests/pch.h"
#include "Parser.h"

#include <sstream>
#include <cctype>
//
#include <algorithm>
#include <vector>
#include <iostream>
#include <limits>

bool Parser::parseNumber(
    const std::string& str,
    long double& value
)
{
    if (str.empty())
    {
        return false;
    }

    if (str == "inf")
    {
        value = std::numeric_limits<long double>::infinity();
        return true;
    }

    if (str == "-inf")
    {
        value = -std::numeric_limits<long double>::infinity();
        return true;
    }

    if (str == "nan")
    {
        value = std::numeric_limits<long double>::quiet_NaN();
        return true;
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
    
    //
    std::transform(
        expr.begin(),
        expr.end(),
        expr.begin(),
        ::tolower
    );
     //

    expr.erase(
        std::remove(expr.begin(), expr.end(), ' '),
        expr.end()
    );

    if (expr.size() < 5)
    {
        return false;
    }

    //

    size_t equalPos = expr.find('=');

    if (equalPos == std::string::npos)
    {
        return false;
    }

    if (expr.substr(equalPos + 1) != "0")
    {
        return false;
    }

    //

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

    int bracketLevel = 0;
    //

    for (size_t i = 0; i < leftPart.size(); i++)
    {
        char ch = leftPart[i];

        if (ch == '(')
        {
            bracketLevel++;
        }

        if (ch == ')')
        {
            bracketLevel--;
        }

        if (
            (ch == '+' || ch == '-') &&
            !current.empty() &&
            bracketLevel == 0
            )
        {
            terms.push_back(current);

            current.clear();
        }

        current += ch;
    }
    //

    if (!current.empty())
    {
        terms.push_back(current);
    }

    //
    for (const auto& term : terms)
    {
        std::cout << "[" << term << "]\n";
    }
    //

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
                if (!evaluateExpression(coef, a))
                {
                    return false;
                }
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
                if (!evaluateExpression(coef, b))
                {
                    return false;
                }
            }
        }
        else
        {
            if (!evaluateExpression(term, c))
            {
                return false;
            }
        }
    }

    //

    return true;
}

bool Parser::evaluateExpression(
    const std::string& expression,
    long double& value
)
{
    //
    std::string expr = expression;

    if (!expr.empty() && expr[0] == '+')
    {
        expr.erase(0, 1);
    }

    if (
        expr.size() >= 2 &&
        expr.front() == '(' &&
        expr.back() == ')'
        )
    {
        return evaluateExpression(
            expr.substr(1, expr.size() - 2),
            value
        );
    }

    //
    //if (
    //    expr.size() >= 2 &&
    //    expr.front() == '(' &&
    //    expr.back() == ')'
    //    )
    //{
    //    return evaluateExpression(
    //        expr.substr(
    //            1,
    //            expr.size() - 2
    //        ),
    //        value
    //    );
    //}
    //

    size_t plusPos =
        expr.find('+');

    if (plusPos != std::string::npos)
    {
        long double left;
        long double right;

        if (!parseNumber(
            expr.substr(0, plusPos),
            left))
        {
            return false;
        }

        if (!parseNumber(
            expr.substr(plusPos + 1),
            right))
        {
            return false;
        }

        value = left + right;

        return true;
    }

    //

    size_t minusPos =
        expr.find('-');

    if (minusPos != std::string::npos &&
        minusPos > 0)
    {
        long double left;
        long double right;

        if (!parseNumber(
            expr.substr(0, minusPos),
            left))
        {
            return false;
        }

        if (!parseNumber(
            expr.substr(minusPos + 1),
            right))
        {
            return false;
        }

        value = left - right;

        return true;
    }

    //

    size_t multiplyPos =
        expr.find('*');

    if (multiplyPos != std::string::npos)
    {
        long double left;
        long double right;

        if (!parseNumber(
            expr.substr(0, multiplyPos),
            left))
        {
            return false;
        }

        if (!parseNumber(
            expr.substr(multiplyPos + 1),
            right))
        {
            return false;
        }

        value = left * right;

        return true;
    }

    //

    size_t dividePos =
        expr.find('/');

    if (dividePos != std::string::npos)
    {
        long double left;
        long double right;

        if (!parseNumber(
            expr.substr(0, dividePos),
            left))
        {
            return false;
        }

        if (!parseNumber(
            expr.substr(dividePos + 1),
            right))
        {
            return false;
        }

        if (right == 0)
        {
            return false;
        }

        value = left / right;

        return true;
    }

    return parseNumber(
        expr,
        value
    );
}


//{
//    std::stringstream ss(expression);
//
//    ss >> value;
//
//    return !ss.fail() && ss.eof();
//}
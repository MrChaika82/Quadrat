//#include "../QuadraticTests/pch.h"

#include "Formatter.h"

#include <sstream>
#include <iomanip>

std::string Formatter::formatNumber(long double value)
{
    std::ostringstream out;

    out << std::fixed << std::setprecision(10) << value;

    std::string result = out.str();

    while (!result.empty() && result.back() == '0')
    {
        result.pop_back();
    }

    if (!result.empty() && result.back() == '.')
    {
        result.pop_back();
    }

    if (result.empty())
    {
        result = "0";
    }

    return result;
}
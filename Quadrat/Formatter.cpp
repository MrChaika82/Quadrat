//#include "../QuadraticTests/pch.h"

#include "Formatter.h"

#include <sstream>
#include <iomanip>
#include <cmath>

std::string Formatter::formatNumber(long double value)
{
    if (std::isnan(value))
    {
        return "nan";
    }

    if (std::isinf(value))
    {
        if (value > 0)
        {
            return "inf";
        }

        return "-inf";
    }

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
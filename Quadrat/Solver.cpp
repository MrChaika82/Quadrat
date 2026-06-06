//#include "../QuadraticTests/pch.h"
#include "Solver.h"
#include "Formatter.h"

#include <cmath>

const long double EPS = 1e-12;

EquationResult Solver::solve(long double a, long double b, long double c)
{
    EquationResult result;

    // Линейное уравнение
    if (std::abs(a) < EPS)
    {
        if (std::abs(b) < EPS)
        {
            if (std::abs(c) < EPS)
            {
                result.type = ResultType::INF;
            }
            else
            {
                result.type = ResultType::NO_SOLUTION;
            }

            return result;
        }

        result.type = ResultType::OK;

        long double x = -c / b;

        result.roots.push_back(
            Formatter::formatNumber(x)
        );

        return result;
    }

    // Дискриминант
    long double D = b * b - 4 * a * c;

    result.discriminant = D;

    result.type = ResultType::OK;

    // Один корень
    if (std::abs(D) < EPS)
    {
        long double x = -b / (2 * a);

        result.roots.push_back(
            Formatter::formatNumber(x)
        );

        return result;
    }

    // Два действительных корня
    if (D > 0)
    {
        long double x1 =
            (-b + std::sqrt(D)) / (2 * a);

        long double x2 =
            (-b - std::sqrt(D)) / (2 * a);

        result.roots.push_back(
            Formatter::formatNumber(x1)
        );

        result.roots.push_back(
            Formatter::formatNumber(x2)
        );

        return result;
    }

    // Комплексные корни
    long double real =
        -b / (2 * a);

    long double imag =
        std::sqrt(-D) / (2 * a);

    std::string root1 =
        Formatter::formatNumber(real)
        + " " +
        Formatter::formatNumber(imag);

    std::string root2 =
        Formatter::formatNumber(real)
        + " " +
        Formatter::formatNumber(-imag);

    result.roots.push_back(root1);
    result.roots.push_back(root2);

    return result;
}
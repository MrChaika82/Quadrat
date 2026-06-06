#include "ResultPrinter.h"

#include <iostream>

void ResultPrinter::print(const EquationResult& result)
{
    switch (result.type)
    {
    case ResultType::OK:

        std::cout << "Решение найдено:\n";

        std::cout
            << "D = "
            << result.discriminant
            << "\n\n";

        std::cout
            << "Количество корней: "
            << result.roots.size()
            << "\n\n";

        for (size_t i = 0; i < result.roots.size(); i++)
        {
            std::cout
                << "x"
                << i + 1
                << " = "
                << result.roots[i]
                << "\n";
        }

        break;

    case ResultType::INF:

        std::cout << "INF";

        break;

    case ResultType::WRONG:

        std::cout << "WRONG";

        break;

    case ResultType::NO_SOLUTION:

        std::cout << "NO SOLUTION";

        break;
    }
}
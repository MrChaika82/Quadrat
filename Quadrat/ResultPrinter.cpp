#include "ResultPrinter.h"

#include <iostream>

void ResultPrinter::print(const EquationResult& result)
{
    switch (result.type)
    {
    case ResultType::OK:

        std::cout << "OK\n";

        std::cout
            << result.roots.size()
            << "\n";

        for (const auto& root : result.roots)
        {
            std::cout << root << "\n";
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
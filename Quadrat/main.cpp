#include <iostream>
#include <sstream>
#include <string>

#include "Parser.h"
#include "Solver.h"
#include "EquationResult.h"
#include "ResultPrinter.h"
#include <windows.h>

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    while (true)
    {
        std::cout << "Введите коэффициенты a b c:\n";

        std::string line;
        std::getline(std::cin, line);

        std::stringstream ss(line);

        std::string aStr;
        std::string bStr;
        std::string cStr;
        std::string extra;

        // Проверяем, что введено ровно 3 значения
        if (!(ss >> aStr >> bStr >> cStr) || (ss >> extra))
        {
            std::cout << "WRONG\n";
        }
        else
        {
            long double a;
            long double b;
            long double c;

            // Проверяем корректность чисел
            if (!Parser::parseNumber(aStr, a) ||
                !Parser::parseNumber(bStr, b) ||
                !Parser::parseNumber(cStr, c))
            {
                std::cout << "WRONG\n";
            }
            else
            {
                EquationResult result =
                    Solver::solve(a, b, c);

                ResultPrinter::print(result);
            }
        }

        std::cout << "\nПродолжить? (y/n): ";

        std::string answer;
        std::getline(std::cin, answer);

        if (answer == "n" || answer == "N")
        {
            break;
        }

        std::cout << "\n";
    }

    return 0;
}
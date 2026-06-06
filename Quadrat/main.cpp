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

        if (Parser::isEquation(line))
        {
            long double a;
            long double b;
            long double c;

            if (Parser::parseEquation(line, a, b, c))
            {
                std::cout << "a = " << a << "\n";
                std::cout << "b = " << b << "\n";
                std::cout << "c = " << c << "\n\n";

                EquationResult result =
                    Solver::solve(a, b, c);

                ResultPrinter::print(result);
            }
            else
            {
                std::cout << "WRONG\n";
            }

            continue;
        }

        std::stringstream ss(line);

        std::string aStr;
        std::string bStr;
        std::string cStr;
        std::string extra;

        if (!(ss >> aStr >> bStr >> cStr) || (ss >> extra))
        {
            std::cout << "WRONG\n";
        }
        else
        {
            long double a;
            long double b;
            long double c;


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
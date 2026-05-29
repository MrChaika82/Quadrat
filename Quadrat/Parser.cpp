//#include "../QuadraticTests/pch.h"
#include "Parser.h"

#include <sstream>
#include <cctype>

bool Parser::parseNumber(
    const std::string& str,
    long double& value
)
{
    // Пустая строка
    if (str.empty())
    {
        return false;
    }

    bool hasDecimalPoint = false;

    for (size_t i = 0; i < str.size(); i++)
    {
        char ch = str[i];

        // Первый символ может быть + или -
        if (i == 0 && (ch == '+' || ch == '-'))
        {
            continue;
        }

        // Проверка точки
        if (ch == '.')
        {
            // Вторая точка запрещена
            if (hasDecimalPoint)
            {
                return false;
            }

            hasDecimalPoint = true;
            continue;
        }

        // Все остальные символы должны быть цифрами
        if (!std::isdigit(ch))
        {
            return false;
        }
    }

    // Преобразование в число
    std::stringstream ss(str);

    ss >> value;

    return !ss.fail() && ss.eof();
}
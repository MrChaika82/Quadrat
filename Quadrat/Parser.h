#pragma once

#include <string>

class Parser
{
public:

    static bool parseNumber(
        const std::string& str,
        long double& value
    );

    static bool isEquation(
        const std::string& str
    );

    static bool parseEquation(
        const std::string& equation,
        long double& a,
        long double& b,
        long double& c
    );

private:

    static bool validateFormat(
        const std::string& str
    );
};
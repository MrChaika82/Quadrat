#pragma once

#include <string>

class Parser
{
public:

    static bool parseNumber(
        const std::string& str,
        long double& value
    );

private:

    static bool validateFormat(
        const std::string& str
    );
};
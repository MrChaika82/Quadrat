#include <gtest/gtest.h>

#include "../Quadrat/Parser.h"

#include "../Quadrat/Solver.h"

TEST(ParserTests, ValidNumber)
{
    long double value;

    bool result =
        Parser::parseNumber("123.45", value);

    ASSERT_TRUE(result);
}
TEST(ParserTests, InvalidNumber)
{
    long double value;

    bool result =
        Parser::parseNumber("12abc", value);

    ASSERT_FALSE(result);
}

TEST(SolverTests, TwoRoots)
{
    EquationResult result =
        Solver::solve(1, -5, 4);

    ASSERT_EQ(result.roots.size(), 2);
}
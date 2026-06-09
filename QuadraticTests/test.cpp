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

TEST(SolverTests, OneRoot)
{
    EquationResult result =
        Solver::solve(1, 2, 1);

    ASSERT_EQ(result.roots.size(), 1);
}

TEST(SolverTests, ComplexRoots)
{
    EquationResult result =
        Solver::solve(1, 0, 1);

    ASSERT_EQ(result.roots.size(), 2);
}

TEST(SolverTests, LinearEquation)
{
    EquationResult result =
        Solver::solve(0, 2, -4);

    ASSERT_EQ(result.roots.size(), 1);
}

TEST(ParserTests, ParseEquation)
{
    long double a;
    long double b;
    long double c;

    bool result =
        Parser::parseEquation(
            "x^2 - 5x + 4 = 0",
            a,
            b,
            c
        );

    ASSERT_TRUE(result);

    ASSERT_EQ(a, 1);
    ASSERT_EQ(b, -5);
    ASSERT_EQ(c, 4);
}

TEST(ParserTests, InvalidEquation)
{
    long double a;
    long double b;
    long double c;

    bool result =
        Parser::parseEquation(
            "x^2 - 5x + 4 = 1",
            a,
            b,
            c
        );

    ASSERT_FALSE(result);
}

TEST(SolverTests, InfiniteSolutions)
{
    EquationResult result =
        Solver::solve(0, 0, 0);

    ASSERT_EQ(
        result.type,
        ResultType::INF
    );
}

TEST(SolverTests, NoSolution)
{
    EquationResult result =
        Solver::solve(0, 0, 5);

    ASSERT_EQ(
        result.type,
        ResultType::NO_SOLUTION
    );
}

TEST(ParserTests, ScientificNotation)
{
    long double value;

    bool result =
        Parser::parseNumber(
            "1e100",
            value
        );

    ASSERT_TRUE(result);
}

TEST(ParserTests, Infinity)
{
    long double value;

    bool result =
        Parser::parseNumber(
            "inf",
            value
        );

    ASSERT_TRUE(result);
}

TEST(ParserTests, EvaluatePlus)
{
    long double value;

    bool result =
        Parser::evaluateExpression(
            "2+3",
            value
        );

    ASSERT_TRUE(result);
    ASSERT_EQ(value, 5);
}

TEST(ParserTests, EvaluateMinus)
{
    long double value;

    bool result =
        Parser::evaluateExpression(
            "10-4",
            value
        );

    ASSERT_TRUE(result);
    ASSERT_EQ(value, 6);
}
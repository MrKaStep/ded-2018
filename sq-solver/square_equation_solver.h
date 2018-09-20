#ifndef SQUARE_EQUATION_SOLVER_H
#define SQUARE_EQUATION_SOLVER_H

/**
 * @file Square equation solver implementation header
 */


#include <cstdlib>
#include <limits>

static constexpr size_t INF_ROOTS = std::numeric_limits<size_t>::max();

namespace SqSolver {

/**
 * @brief Inner class for storing result
 */
struct Result {
    size_t RootCount;
    double Root1;
    double Root2;

    explicit Result(size_t rootCount, double root1 = 0, double root2 = 0) noexcept
        : RootCount(rootCount)
        , Root1(root1)
        , Root2(root2)
    {
    }
};

const Result INF_ROOTS_RESULT = Result(INF_ROOTS, 0, 0);

/**
 * @brief Struct for equation storage
 */
struct Equation {
    double a;
    double b;
    double c;
};

/**
 * @brief Checks if equation is linear
 *
 * Check is performed by comparing the Equation::a part of @p equation
 *
 * @param equation
 * @return true iff @p equation is linear
 */
bool IsLinear(Equation& equation);

/**
 * @brief Solves linear equation
 *
 * Checks if equation is linear. If so, returns result with 0, 1, of INF_RESULT roots.
 * Otherwise, fails on assertion
 *
 * @param equation
 * @return Result with roots description
 */
Result SolveLinear(Equation& equation);

/**
 * @brief Solves square equation
 *
 * If equation is linear, IsLinear(\p equation) is called.
 *
 * Otherwise, solves equation using discriminant method
 *
 * @param equation
 * @return Result with roots description
 */
Result SolveSquareInternal(Equation& equation);

} /// namespace SqSolver

/**
 * @brief User interface wrapper for SqSolver::SolveSquareInternal
 * @param a
 * @param b
 * @param c
 * @param rootCount
 * @param root1
 * @param root2
 */
void SolveSquare(double a, double b, double c, size_t* rootCount, double* root1, double* root2);

#endif /// SQUARE_EQUATION_SOLVER_H
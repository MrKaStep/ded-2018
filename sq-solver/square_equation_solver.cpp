#include "square_equation_solver.h"

#include <util.h>
#include <cassert>

namespace SqSolver {

using Util::IsZero;

bool IsLinear(const Equation& equation) {
    return IsZero(equation.a);
}

Result SolveLinear(const Equation& equation) {
    assert(IsLinear(equation));

    if (IsZero(equation.b)) {
        if (IsZero(equation.c)) {
            return INF_ROOTS_RESULT;
        }

        return Result(0);
    }

    return Result(1, -equation.c / equation.b, 0);
}

Result SolveSquareInternal(const Equation& equation) {
    if (IsLinear(equation)) {
        return SolveLinear(equation);
    }

    double discriminant = equation.b * equation.b - 4 * equation.a * equation.c;



    if (Util::IsLessOrEqual(discriminant, 0)) {
        if (IsZero(discriminant)) {
            return Result(1, -equation.b / (2 * equation.a));
        }

        return Result(0);
    }

    double discriminantRoot = sqrt(discriminant);

    return Result(2,
                  (-equation.b - discriminantRoot) / (2 * equation.a),
                  (-equation.b + discriminantRoot) / (2 * equation.a));
}

} /// namespace SqSolver

void SolveSquare(double a, double b, double c, size_t* rootCount, double* root1, double* root2) {
    auto result = SqSolver::SolveSquareInternal({a, b, c});

    *rootCount = result.RootCount;
    *root1 = result.Root1;
    *root2 = result.Root2;
}
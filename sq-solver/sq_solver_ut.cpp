#include <my_test.h>
#include "square_equation_solver.h"

#include <iostream>


/**
 * Checks that SolveSquare produces expected result for given equation
 *
 * @param a
 * @param b
 * @param c
 * @param expCount expected root count
 * @param root1 first expected root
 * @param root2 second expected root
 */
static void CheckRoots(double a, double b, double c, size_t expCount, double root1 = 0, double root2 = 0) {
    size_t count;
    double x1;
    double x2;

    SolveSquare(a, b, c, &count, &x1, &x2);

    ASSERT_EQ(count, expCount);

    if (count == INF_ROOTS || count == 0) {
        return;
    }

    if (count > 0) {
        ASSERT_DBL_EQ(root1, x1);
    }

    if (count > 1) {
        ASSERT_DBL_EQ(root2, x2);
    }
}

TEST_SUITE(Test) {
    TEST_CASE(NoRoots) {
        CheckRoots(0, 0, 1, 0);
        CheckRoots(0, 0, 1e100, 0);
    }

    TEST_CASE(Infinite) {
        CheckRoots(0, 0, 0, INF_ROOTS);
    }

    TEST_CASE(Linear) {
        CheckRoots(0, 1, -1, 1, 1);
        CheckRoots(0, 1e2, -1, 1, 1e-2);
        CheckRoots(0, 2, 100, 1, -50);
    }

    TEST_CASE(NoRootsSquare) {
        CheckRoots(1, 0, 1, 0);
        CheckRoots(1e100, 0, 1e100, 0);
        CheckRoots(1, 1, 1, 0);
    }

    TEST_CASE(OneRoot) {
        CheckRoots(1, 0, 0, 1, 0);
        CheckRoots(1, -2, 1, 1, 1);
    }

    TEST_CASE(TwoRoots) {
        CheckRoots(1, 0, -1, 2, -1, 1);
        CheckRoots(1, 0, -2, 2, -sqrt(2.), sqrt(2.));
    }
}

int main() {
    TestRunner::RunTests();
    return 0;
}

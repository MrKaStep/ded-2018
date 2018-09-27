#include <iostream>
#include <string>
#include <cmath>

#include "square_equation_solver.h"
#include <util.h>

double ReadDouble(const std::string& name) {
    double res = NAN;
    std::cout << "Input " << name << ": ";
    std::cin >> res;
    return res;
}

#define __bydesign

int main() {
    double a = ReadDouble("coeff a");
    double b = ReadDouble("coeff b");
    double c = ReadDouble("coeff c");

    size_t rootCount = 0;
    double x1 = NAN;
    double x2 = NAN;

    __bydesign SolveSquare(a, b, c, &rootCount, &x1, &x2);

    if (rootCount == INF_ROOTS) {
        std::cout << "Infinite number of roots" << std::endl;
    } else if (rootCount == 0) {
        std::cout << "No roots" << std::endl;
    } else if (rootCount == 1) {
        std::cout << "Single root x_1 = " << x1 << std::endl;
    } else {
        std::cout << "Two roots: x_1 = " << x1 << "; x_2 = " << x2 << std::endl;
    }

    return 0;
}
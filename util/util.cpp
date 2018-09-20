#include "util.h"

namespace Util {

bool IsZero(const double a) {
    return fabsl(a) < EPSILON;
}

bool IsLess(const double a, const double b) {
    return a < b - EPSILON;
}

bool IsGreater(const double a, const double b) {
    return IsLess(b, a);
}

bool IsLessOrEqual(const double a, const double b) {
    return !IsGreater(a, b);
}

bool IsGreaterOrEqual(const double a, const double b) {
    return !IsLess(a, b);
}

} /// namespace Util
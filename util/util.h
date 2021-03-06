#ifndef UTIL_H
#define UTIL_H

#include <cmath>
#include <limits>

/**
 * @brief epsilon for math operations
 */
const double EPSILON = std::numeric_limits<double>::epsilon();

/**
 * @brief branch prediction optimization
 */
#define LIKELY(x) __builtin_expect(!!(x), 1)

/**
 * @brief branch prediction optimization
 */
#define UNLIKELY(x) __builtin_expect(!!(x), 0)

namespace Util {

bool IsZero(double a);
bool IsLess(double a, double b);
bool IsGreater(double a, double b);
bool IsLessOrEqual(double a, double b);
bool IsGreaterOrEqual(double a, double b);

} /// namespace Util

#endif /// UTIL_H
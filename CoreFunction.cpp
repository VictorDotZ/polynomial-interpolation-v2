#include "CoreFunction.hpp"

#include <cmath>

// Runge function
// double F(double x) { return 1.0 / (1.0 + 25.0 * x * x); }

double F(double x) { return std::abs(x); }

// double F(double x) { return std::pow(x, 5); }

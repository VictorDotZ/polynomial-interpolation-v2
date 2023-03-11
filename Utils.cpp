#include "Utils.hpp"
#include "CoreFunction.hpp"

#include <cmath>
#include <iostream>

// Horner's method
double applyPolynomialCanonical(const std::vector<double>& a, double x)
{
	double res = a[a.size() - 1] * x;
	for (size_t i = a.size() - 2; i > 0; --i) {
		res += a[i];
		res *= x;
	}
	return res + a[0];
}

void printRow(double x_i, const std::vector<double>& canonicalCoefs)
{
	const double f = F(x_i);
	const double canonical = applyPolynomialCanonical(canonicalCoefs, x_i);
	std::cout << std::scientific;
	std::cout << x_i << "\t" << f << "\t" << canonical << "\t"
	          << std::abs(canonical - f) << std::endl;
}

// число точек не поменялось, всё ок
void printResult(
    const std::vector<double>& x, const std::vector<double>& canonicalCoefs)
{
	double step = 0.0;
	for (size_t i = 0; i + 1 < x.size(); i++) {
		step = (x[i + 1] - x[i]) / 3.0;
		printRow(x[i] + 0 * step, canonicalCoefs);
		printRow(x[i] + 1 * step, canonicalCoefs);
		printRow(x[i] + 2 * step, canonicalCoefs);
	}
	printRow(x[x.size() - 1], canonicalCoefs);
}
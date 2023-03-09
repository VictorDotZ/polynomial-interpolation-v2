#include "Utils.hpp"
#include "CoreFunction.hpp"

#include <cmath>
#include <iostream>

double phiNumerator(size_t i, double x_i, const std::vector<double>& x)
{
	double numerator = 1.0;

	for (size_t j = 0; j < x.size(); ++j) {
		if (j == i)
			continue;

		numerator *= (x_i - x[j]);
	}
	return numerator;
}

double phiDenominator(size_t i, const std::vector<double>& x)
{
	double denominator = 1.0;

	for (size_t j = 0; j < x.size(); ++j) {
		if (j == i)
			continue;

		denominator *= (x[i] - x[j]);
	}
	return denominator;
}

static double applyPolynomialLagrangian(
    const std::vector<double>& x, const std::vector<double>& coefs, double x_i)
{
	double res = 0.0;
	for (size_t i = 0; i < x.size(); i++)
		res += coefs[i] * phiNumerator(i, x_i, x);
	return res;
}

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

void printRow(double x_i, const std::vector<double>& x,
    const std::vector<double>& canonicalCoefs,
    const std::vector<double>& lagrangianCoefs)
{
	const double f = F(x_i);
	const double canonical = applyPolynomialCanonical(canonicalCoefs, x_i);
	const double lagrange = applyPolynomialLagrangian(x, lagrangianCoefs, x_i);
	std::cout << std::scientific;
	std::cout << x_i << "\t" << f << "\t" << canonical << "\t"
	          << std::abs(canonical - f) << "\t" << lagrange << "\t"
	          << std::abs(lagrange - f) << std::endl;
}

void printResult(const std::vector<double>& x,
    const std::vector<double>& canonicalCoefs,
    const std::vector<double>& lagrangianCoefs)
{
	double step = 0.0;
	for (size_t i = 0; i + 1 < x.size(); i++) {
		step = (x[i + 1] - x[i]) / 3.0;
		printRow(x[i] + 0 * step, x, canonicalCoefs, lagrangianCoefs);
		printRow(x[i] + 1 * step, x, canonicalCoefs, lagrangianCoefs);
		printRow(x[i] + 2 * step, x, canonicalCoefs, lagrangianCoefs);
	}
	printRow(x[x.size() - 1], x, canonicalCoefs, lagrangianCoefs);
}
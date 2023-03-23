#include "Utils.hpp"
#include "CoreFunction.hpp"
#include "GaussianElimination.hpp"

#include <cmath>
#include <iostream>

// теперь в последней колонке (-1) ^ i, где i - индекс строки
// это позволит вычислить h, поэтому это не классическая матрица Вандермонда
std::vector<double> getModifiedVandermondeMatrix(
    const std::vector<double>& x, size_t N)
{
	auto A = std::vector<double>(N * N);

	for (size_t i = 0; i < N; ++i) {
		// последний столбец заполняется отдельно
		for (size_t j = 0; j < N - 1; ++j)
			A(i, j) = std::pow(x[i], j);

		A(i, N - 1) = std::pow(-1.0, i);
	}

	return A;
}

std::vector<double> Default::getCanonicalCoefficients(
    const std::vector<double>& x, std::vector<double>& y)
{
	auto A = getModifiedVandermondeMatrix(x, x.size());

	return gaussianEliminationPickMaxColumn(A, y);
}

// Horner's method
double Default::applyPolynomialCanonical(const std::vector<double>& a, double x)
{
	double res = a[a.size() - 1] * x;
	for (size_t i = a.size() - 2; i > 0; --i) {
		res += a[i];
		res *= x;
	}
	return res + a[0];
}

int sign(double val) { return std::signbit(val); }

void printRow(double x_i, const std::vector<double>& canonicalCoefs)
{
	const double f = F(x_i);
	const double canonical
	    = Default::applyPolynomialCanonical(canonicalCoefs, x_i);
	std::cout << std::scientific;
	std::cout << x_i << "\t" << f << "\t" << canonical << "\t"
	          << std::abs(canonical - f) << std::endl;
}

// число точек не поменялось, всё ок
void printResult(
    const std::vector<double>& x, const std::vector<double>& canonicalCoefs)
{
	for (size_t i = 0; i < x.size(); ++i)
		printRow(x[i], canonicalCoefs);
}
#include "CoreFunction.hpp"
#include "GaussianElimination.hpp"
#include "Utils.hpp"

#include <cmath>
#include <iostream>

std::vector<double> getVandermondeMatrix(const std::vector<double>& x, size_t N)
{
	auto A = std::vector<double>(N * N);

	for (size_t i = 0; i < N; ++i)
		for (size_t j = 0; j < N; ++j)
			A[i * N + j] = std::pow(x[i], j);

	return A;
}

std::vector<double> getCanonicalCoefficients(
    std::vector<double> x, std::vector<double> y)
{
	auto A = getVandermondeMatrix(x, x.size());

	return gaussianEliminationPickMaxColumn(A, y);
}

std::vector<double> getLagrangianCoefficients(
    const std::vector<double>& x, const std::vector<double>& y)
{

	auto coefs = std::vector<double>(x.size());

	for (size_t i = 0; i < x.size(); ++i)
		coefs[i] = y[i] / phiDenominator(i, x);

	return coefs;
}

int main(int argc, char* argv[])
{
	if (argc != 1)
		return -1;

	size_t N;

	std::cin >> N;

	auto x = std::vector<double>(N);
	auto y = std::vector<double>(N);

	for (size_t i = 0; i < N; ++i) {
		std::cin >> x[i];
		std::cin >> y[i];
	}

	auto canonicalCoefs = getCanonicalCoefficients(x, y);
	auto lagrangianCoefs = getLagrangianCoefficients(x, y);

	printResult(x, canonicalCoefs, lagrangianCoefs);

	return 0;
}
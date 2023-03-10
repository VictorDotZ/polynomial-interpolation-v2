#include "CoreFunction.hpp"
#include "GaussianElimination.hpp"
#include "Utils.hpp"

#include <cmath>
#include <iostream>

std::vector<double> getModifiedVandermondeMatrix(
    const std::vector<double>& x, size_t N);
std::vector<double> getCanonicalCoefficients(
    const std::vector<double>& x, std::vector<double>& y);

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

std::vector<double> getCanonicalCoefficients(
    const std::vector<double>& x, std::vector<double>& y)
{
	auto A = getModifiedVandermondeMatrix(x, x.size());

	return gaussianEliminationPickMaxColumn(A, y);
}

int main()
{
	std::cin.exceptions(std::ios::failbit | std::ios::badbit);
	size_t N;

	std::cin >> N;

	auto x = std::vector<double>(N);
	auto y = std::vector<double>(N);

	for (size_t i = 0; i < N; ++i) {
		std::cin >> x[i];
		std::cin >> y[i];
	}

	auto canonicalCoefs = getCanonicalCoefficients(x, y);

	printResult(x, canonicalCoefs);

	return 0;
}
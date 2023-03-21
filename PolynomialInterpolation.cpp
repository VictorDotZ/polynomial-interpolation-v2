#include "CoreFunction.hpp"
#include "GaussianElimination.hpp"
#include "Utils.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>

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

std::vector<size_t> getBasisIndices(unsigned n_coeffs_with_h)
{
	auto basisIds = std::vector<size_t>(n_coeffs_with_h);

	std::iota(basisIds.begin(), basisIds.end(), 1);

	return basisIds;
}

std::tuple<std::vector<double>, std::vector<double>> getBasis(
    const std::vector<double>& x, const std::vector<double>& y,
    const std::vector<size_t>& basisIds)
{
	auto basisX = std::vector<double>(basisIds.size());
	auto basisY = std::vector<double>(basisIds.size());

	for (auto idx : basisIds) {
		basisX.push_back(x[idx]);
		basisY.push_back(y[idx]);
	}

	return std::make_tuple(basisX, basisY);
}

std::vector<double> getValleePoussinCanonicalCoefficitnts(
    const std::vector<double>& x, std::vector<double>& y,
    const size_t nCoefficientsWithH)
{
	auto basisIds = getBasisIndices(nCoefficientsWithH);
	std::vector<double> coeffs;

	do {
		auto [basisX, basisY] = getBasis(x, y, basisIds);

		try {
			coeffs = getCanonicalCoefficients(basisX, basisY);
		} catch (std::runtime_error& e) {
			break;
		}

	} while (true);
}

int main(int argc, char* argv[])
{
	std::cin.exceptions(std::ios::failbit | std::ios::badbit);
	size_t N;
	size_t polynomialDegree;

	if (argc >= 2)
		polynomialDegree = std::stoull(argv[1]);

	// the number of points
	// should be greatest then or equeal to polynomail degree
	// for vallee poussin method
	std::cin >> N;

	if (polynomialDegree >= N - 1)
		return -1;

	auto x = std::vector<double>(N);
	auto y = std::vector<double>(N);

	for (size_t i = 0; i < N; ++i)
		std::cin >> x[i] >> y[i];

	size_t nCoefficientsWithH = polynomialDegree + 2;

	auto canonicalCoefs = (nCoefficientsWithH == N)
	    ? getCanonicalCoefficients(x, y)
	    : getValleePoussinCanonicalCoefficitnts(x, y, nCoefficientsWithH);

	printResult(x, canonicalCoefs);

	return 0;
}
#include "CoreFunction.hpp"
#include "GaussianElimination.hpp"
#include "Utils.hpp"
#include "VallePoussin.hpp"

#include <iostream>

/*
    в предыдущей реализации всё зависело от количества точек.
    То есть подавалась одна лишняя точка, из-за чего
    размерность вектора коэффициентов была на 1 больше нужной

*/

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

	std::vector<double> canonicalCoefs;

	if (nCoefficientsWithH == N) {
		printResult(x, Default::getCanonicalCoefficients(x, y));
	} else {
		auto solver = VallePoussinSolver(N, polynomialDegree, x, y, 1e-5);
		printResult(x, solver.getCanonicalCoefficients());
	}

	return 0;
}
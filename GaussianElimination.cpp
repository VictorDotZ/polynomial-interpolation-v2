#include "GaussianElimination.hpp"

#include <cmath>

#include <stdexcept>

std::vector<double> gaussianEliminationPickMaxColumn(
    std::vector<double> A, std::vector<double> x)
{
	size_t N = x.size();
	size_t maxColIdx = 0;
	double maxColValue = 0.0;
	double c = 0.0;

	for (size_t j = 0; j < N; ++j) {
		maxColValue = std::abs(A(j, j));
		maxColIdx = j;

		// find max elem between columns
		for (size_t i = j; i < N; ++i) {
			if (std::abs(A(i, j)) > maxColValue) {
				maxColIdx = i;
				maxColValue = std::abs(A(i, j));
			}
		}

		// maxColValue is absolute value already
		if (!(maxColValue >= std::numeric_limits<double>::epsilon()))
			throw std::runtime_error("pseudo zero division has been occured");

		// reorder rows
		if (maxColIdx != j) {
			for (size_t i = j; i < N; ++i)
				std::swap(A(j, i), A(maxColIdx, i));
			std::swap(x[j], x[maxColIdx]);
		}

		// divide all row by first element
		c = 1.0 / A(j, j);
		for (size_t i = j; i < N; ++i)
			A(j, i) *= c;

		x[j] *= c;

		// subtract elements under diagonal
		for (size_t i = j + 1; i < N; ++i) {
			c = A(i, j);
			for (size_t k = j; k < N; ++k)
				A(i, k) -= c * A(j, k);

			x[i] -= c * x[j];
		}
	}

	for (size_t j = N; j >= 1; --j) {
		for (size_t i = 0; i < j - 1; ++i) {
			c = A(i, j - 1);
			x[i] -= c * x[j - 1];
			A(i, j - 1) = 0.0;
		}
	}

	return x;
}
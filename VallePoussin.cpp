#include "VallePoussin.hpp"
#include "Utils.hpp"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <vector>

VallePoussinSolver::VallePoussinSolver(size_t N, size_t polynomialDegree,
    const std::vector<double>& x, const std::vector<double>& y,
    double eps = 1e-5)
    : m_N(N)
    , m_polynomialDegree(polynomialDegree)
    , m_x(x)
    , m_y(y)
    , m_eps(eps)
{
	m_nCoefficientsWithH = m_polynomialDegree + 2;

	m_basisIds = std::vector<size_t>(m_nCoefficientsWithH);

	std::iota(m_basisIds.begin(), m_basisIds.end(), 0);
};

std::vector<double> VallePoussinSolver::getCanonicalCoefficients()
{
	do {
		auto [basisX, basisY] = getBasis();

		try {
			m_coeffs = Default::getCanonicalCoefficients(basisX, basisY);
		} catch (std::runtime_error& e) {
			break;
		}

		auto [hMax, hMaxIdx] = getMaxDeviationWithPos();

		if (std::abs(std::abs(m_coeffs.back()) - hMax) < m_eps)
			break;

		if (!isAdjustable(hMaxIdx))
			break;

	} while (true);

	return std::vector<double>(m_coeffs.begin(), m_coeffs.end() - 1);
}

std::tuple<std::vector<double>, std::vector<double>>
VallePoussinSolver::getBasis()
{
	auto basisX = std::vector<double>();
	auto basisY = std::vector<double>();

	for (auto idx : m_basisIds) {
		basisX.push_back(m_x[idx]);
		basisY.push_back(m_y[idx]);
	}

	return std::make_tuple(basisX, basisY);
}

/*
    коэффициентов в векторе на 1 больше из-за h,
    но h не используется для вычисления значения полинома
    поэтому обернём в отдельный метод правильное вычисление
*/
double VallePoussinSolver::applyPolynomialCanonical(double x)
{
	return Default::applyPolynomialCanonical(
	    std::vector(m_coeffs.begin(), m_coeffs.end() - 1), x);
}

double VallePoussinSolver::getDelta(size_t idx)
{
	return m_y[idx] - applyPolynomialCanonical(m_x[idx]);
}

std::tuple<double, int> VallePoussinSolver::getMaxDeviationWithPos()
{
	std::vector<double> res(m_x.size());
	std::iota(res.begin(), res.end(), 0);

	auto mapper = [this](size_t i) { return std::abs(getDelta(i)); };

	std::transform(res.begin(), res.end(), res.begin(), mapper);

	auto hMax = std::max_element(res.begin(), res.end());

	return std::make_tuple(*hMax, std::distance(res.begin(), hMax));
}

bool VallePoussinSolver::isAdjustable(size_t hMaxIdx)
{
	auto leftBound = m_basisIds.front();
	auto rightBound = m_basisIds.back();
	const auto maxDeviationSign = sign(getDelta(hMaxIdx));

	if (hMaxIdx < leftBound) {
		if (maxDeviationSign != sign(getDelta(leftBound)))
			std::shift_right(m_basisIds.begin(), m_basisIds.end(), 1);

		m_basisIds.front() = hMaxIdx;
		return true;
	}

	if (hMaxIdx > rightBound) {
		if (maxDeviationSign != sign(getDelta(rightBound)))
			std::shift_left(m_basisIds.begin(), m_basisIds.end(), 1);

		m_basisIds.back() = hMaxIdx;
		return true;
	}

	auto rightNeighbour
	    = std::lower_bound(m_basisIds.begin(), m_basisIds.end(), hMaxIdx);

	if (*rightNeighbour == hMaxIdx)
		return false;

	auto leftNeighbour = rightNeighbour - 1;

	if (maxDeviationSign == sign(getDelta(*leftNeighbour))) {
		*leftNeighbour = hMaxIdx;
	} else {
		*rightNeighbour = hMaxIdx;
	}

	return true;
}
#pragma once

#include <vector>

class VallePoussinSolver {

public:
	VallePoussinSolver(size_t N, size_t polynomialDegree, std::vector<double> x,
	    std::vector<double> y, double eps /*= 1e-5*/);

	std::vector<double> getCanonicalCoefficients();

private:
	std::tuple<std::vector<double>, std::vector<double>> getBasis();

	/*
	    коэффициентов в векторе на 1 больше из-за h,
	    но h не используется для вычисления значения полинома
	    поэтому обернём в отдельный метод правильное вычисление
	*/
	double applyPolynomialCanonical(double x);
	double getDelta(size_t idx);

	std::tuple<double, int> getMaxDeviationWithPos();

	bool isAdjustable(size_t hMaxIdx);

	size_t m_N;
	size_t m_polynomialDegree;
	size_t m_nCoefficientsWithH;

	std::vector<double> m_x;
	std::vector<double> m_y;

	/*
	    тут N+1 коэффициент полинома + h
	    модифицированный вандермонд с гауссом с первой части
	    дают как раз такую структуру ответа по выбранному базису
	*/
	std::vector<double> m_coeffs;

	/*
	    тут у нас m_polynomialDegree + 2 элементов, т.е.
	    m_polynomialDegree + 1 для настоящих коэффициентов
	    и ещё + 1 для h.
	    Итого в базисе будет ровно столько же точек, сколько было
	    и в предыдущей части задачи, а значит пайплайн отработает как надо
	*/
	std::vector<size_t> m_basisIds;
	const double m_eps;
};
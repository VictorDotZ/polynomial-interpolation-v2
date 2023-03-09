#include <vector>

double applyPolynomialCanonical(const std::vector<double>& a, double x);

double phiNumerator(size_t i, double x_i, const std::vector<double>& x);

double phiDenominator(size_t i, const std::vector<double>& x);

void printRow(double x_i, const std::vector<double>& x,
    const std::vector<double>& canonicalCoefs,
    const std::vector<double>& lagrangianCoefs);

void printResult(const std::vector<double>& x,
    const std::vector<double>& canonicalCoefs,
    const std::vector<double>& lagrangianCoefs);
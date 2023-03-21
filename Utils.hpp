#include <cmath>
#include <vector>

std::vector<double> getModifiedVandermondeMatrix(
    const std::vector<double>& x, size_t N);

namespace Default {
std::vector<double> getCanonicalCoefficients(
    std::vector<double> x, std::vector<double> y);

double applyPolynomialCanonical(const std::vector<double>& a, double x);
};

int sign(double val);

// Метод лагранжа неприменим в данной модификации задачи
// Вывод его коэффициентов более не нужен
void printRow(double x_i, const std::vector<double>& canonicalCoefs);

void printResult(
    const std::vector<double>& x, const std::vector<double>& canonicalCoefs);
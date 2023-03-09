#include <vector>

double applyPolynomialCanonical(const std::vector<double>& a, double x);

// Метод лагранжа неприменим в данной модификации задачи
// Вывод его коэффициентов более не нужен
void printRow(double x_i, const std::vector<double>& x,
    const std::vector<double>& canonicalCoefs);

void printResult(
    const std::vector<double>& x, const std::vector<double>& canonicalCoefs);
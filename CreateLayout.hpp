#pragma once
#include <vector>

namespace NodesGenerator {
std::vector<double> chebyshev(size_t N, double leftBound, double rightBound);
std::vector<double> uniform(size_t N, double leftBound, double rightBound);
std::vector<double> random(size_t N, double leftBound, double rightBound);
}
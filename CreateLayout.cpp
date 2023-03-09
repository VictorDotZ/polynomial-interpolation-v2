#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <random>
#include <unordered_map>
#include <vector>

#include "CoreFunction.hpp"

namespace NodesGenerator {

std::vector<double> chebyshev(size_t N, double leftBound, double rightBound)
{
	const double shift = 0.5 * (leftBound + rightBound);
	const double scale = 0.5 * (leftBound - rightBound);

	auto nodes = std::vector<double>(N);

	for (size_t k = 0; k < N; ++k) {
		nodes[N - 1 - k]
		    = shift + scale * std::cos(M_PI * (2.0 * k + 1.0) / (2.0 * N));
	}

	return nodes;
}

std::vector<double> uniform(size_t N, double leftBound, double rightBound)
{
	const double step = (rightBound - leftBound) / (N - 1.0);

	auto nodes = std::vector<double>(N);

	nodes[0] = leftBound;

	for (size_t i = 0; i + 1 < N; ++i)
		nodes[i + 1] = nodes[i] + step;

	return nodes;
}

std::vector<double> random(size_t N, double leftBound, double rightBound)
{
	std::random_device rnd_device;
	std::mt19937 mersenne_engine { rnd_device() };
	std::uniform_real_distribution<double> dist { leftBound, rightBound };
	auto gen = [&dist, &mersenne_engine]() { return dist(mersenne_engine); };

	auto nodes = std::vector<double>(N);

	std::generate(nodes.begin(), nodes.end(), gen);
	std::sort(nodes.begin(), nodes.end());

	return nodes;
}

}

using method = std::function<std::vector<double>(size_t, double, double)>;

std::unordered_map<std::string, method> methods = {
	{ "ch", NodesGenerator::chebyshev },
	{ "un", NodesGenerator::uniform },
	{ "rnd", NodesGenerator::random },
};

int main(int argc, char* argv[])
{
	if (argc != 5) {
		return -1;
	}

	size_t N = std::stoull(argv[1]);
	double leftBound = std::stod(argv[2]);
	double rightBound = std::stod(argv[3]);
	std::string method = std::string(argv[4]);

	if (!methods.contains(method))
		return -2;

	auto nodes = methods[method](N, leftBound, rightBound);

	std::cout << nodes.size() << std::endl;
	std::cout.precision(17);
	for (auto x : nodes)
		std::cout << x << "\t" << F(x) << std::endl;

	return 0;
}
#include "NodesGenerator.hpp"
#include <algorithm>
#include <cmath>
#include <random>
#include <stdexcept>

NodesGenerator::NodesGenerator()
    : m_methods({ { "ch", NodesGenerator::chebyshev },
        { "un", NodesGenerator::uniform },
        { "rnd", NodesGenerator::random } }) {};

NodesGenerator::NodesGenerator(std::string methodName)
    : NodesGenerator::NodesGenerator()
{
	setMethod(methodName);
}

void NodesGenerator::setMethod(std::string methodName)
{
	if (!m_methods.contains(methodName))
		throw std::invalid_argument("Method " + methodName + "does not exist");

	m_selectedMethod = m_methods[methodName];
}

std::vector<double> NodesGenerator::generate(
    size_t N, double leftBound, double rightBound)
{
	auto nodes = m_selectedMethod(N, leftBound, rightBound);

	std::sort(nodes.begin(), nodes.end());
	return nodes;
}

const std::vector<double> NodesGenerator::chebyshev(
    size_t N, double leftBound, double rightBound)
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

const std::vector<double> NodesGenerator::uniform(
    size_t N, double leftBound, double rightBound)
{
	const double step = (rightBound - leftBound) / (N - 1.0);

	auto nodes = std::vector<double>(N);

	nodes[0] = leftBound;

	for (size_t i = 0; i + 1 < N; ++i)
		nodes[i + 1] = nodes[i] + step;

	return nodes;
}

const std::vector<double> NodesGenerator::random(
    size_t N, double leftBound, double rightBound)
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
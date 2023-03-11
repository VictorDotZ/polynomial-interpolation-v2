#pragma once
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

class NodesGenerator {

public:
	using method = std::function<std::vector<double>(size_t, double, double)>;

	NodesGenerator();
	NodesGenerator(std::string methodName);

	void setMethod(std::string methodName);

	std::vector<double> generate(size_t N, double leftBound, double rightBound);

private:
	const static std::vector<double> chebyshev(
	    size_t N, double leftBound, double rightBound);
	const static std::vector<double> uniform(
	    size_t N, double leftBound, double rightBound);
	const static std::vector<double> random(
	    size_t N, double leftBound, double rightBound);
	std::unordered_map<std::string, method> m_methods;
	method m_selectedMethod;
};

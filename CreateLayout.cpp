#include <iostream>

#include <memory>

#include "CoreFunction.hpp"
#include "NodesGenerator.hpp"

int main(int argc, char* argv[])
{
	if (argc != 5) {
		return -1;
	}

	size_t N = std::stoull(argv[1]);
	double leftBound = std::stod(argv[2]);
	double rightBound = std::stod(argv[3]);
	std::string method = std::string(argv[4]);

	auto nodesGenerator
	    = std::unique_ptr<NodesGenerator>(new NodesGenerator(method));

	auto nodes = nodesGenerator->generate(N, leftBound, rightBound);

	std::cout << nodes.size() << std::endl;
	std::cout.precision(17);
	for (auto x : nodes)
		std::cout << x << "\t" << F(x) << std::endl;

	return 0;
}
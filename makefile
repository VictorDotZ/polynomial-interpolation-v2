CC=g++

FLAGS=	-std=c++2a -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align  \
		-Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security \
		-Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long  \
		-Wcast-qual -Wno-suggest-attribute=format -Wpedantic \
		-Wmissing-declarations -Wall -Werror -Wextra -Wfloat-equal -Wshadow \
		-Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Wno-conversion  \
		-Wdisabled-optimization -Wredundant-decls -Wunused-value -Wno-deprecated \

all: CreateLayout.out PolynomialInterpolation.out

PolynomialInterpolation.out: PolynomialInterpolation.o GaussianElimination.o CoreFunction.o Utils.o
	$(CC) $(FLAGS) -o PolynomialInterpolation.out PolynomialInterpolation.o GaussianElimination.o CoreFunction.o Utils.o

PolynomialInterpolation.o: PolynomialInterpolation.cpp CoreFunction.hpp
	$(CC) $(FLAGS) -c PolynomialInterpolation.cpp

Utils.o: Utils.cpp Utils.hpp
	$(CC) $(FLAGS) -c Utils.cpp

GaussianElimination.o: GaussianElimination.cpp GaussianElimination.hpp
	$(CC) $(FLAGS) -c GaussianElimination.cpp

CreateLayout.out: CreateLayout.o CoreFunction.o NodesGenerator.o
	$(CC) $(FLAGS) -o CreateLayout.out CreateLayout.o CoreFunction.o NodesGenerator.o

CreateLayout.o: CreateLayout.cpp CoreFunction.hpp NodesGenerator.hpp
	$(CC) $(FLAGS) -c CreateLayout.cpp

NodesGenerator.o: NodesGenerator.cpp NodesGenerator.hpp
	$(CC) $(FLAGS) -c NodesGenerator.cpp

CoreFunction.o: CoreFunction.cpp CoreFunction.hpp
	$(CC) $(FLAGS) -c CoreFunction.cpp

clean:
	rm -rf *.o *.out *.a *.txt *.png
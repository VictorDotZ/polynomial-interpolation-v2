CC=g++
FLAGS=-std=c++20

all: CreateLayout.out PolynomialInterpolation.out

PolynomialInterpolation.out: PolynomialInterpolation.o GaussianElimination.o CoreFunction.o Utils.o
	$(CC) $(FLAGS) -o PolynomialInterpolation.out PolynomialInterpolation.o GaussianElimination.o CoreFunction.o Utils.o

PolynomialInterpolation.o: PolynomialInterpolation.cpp CoreFunction.hpp
	$(CC) $(FLAGS) -c PolynomialInterpolation.cpp

Utils.o: Utils.cpp Utils.hpp
	$(CC) $(FLAGS) -c Utils.cpp

GaussianElimination.o: GaussianElimination.cpp GaussianElimination.hpp
	$(CC) $(FLAGS) -c GaussianElimination.cpp

CreateLayout.out: CreateLayout.o CoreFunction.o
	$(CC) $(FLAGS) -o CreateLayout.out CreateLayout.o CoreFunction.o

CreateLayout.o: CreateLayout.cpp CoreFunction.hpp
	$(CC) $(FLAGS) -c CreateLayout.cpp

CoreFunction.o: CoreFunction.cpp CoreFunction.hpp
	$(CC) $(FLAGS) -c CoreFunction.cpp

clean:
	rm -rf *.o *.out *.a *.txt *.png
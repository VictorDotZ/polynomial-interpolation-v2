#pragma once

#include <vector>

// вынесено в хедер, т.к. позволяет удобнее работать с матрицей Вандермонда
#define A(i, j) A[(i)*N + (j)]

std::vector<double> gaussianEliminationPickMaxColumn(
    std::vector<double> A, std::vector<double> x);
#pragma once

#include <vector>

class Matrix{
public:
    Matrix(size_t numRows, size_t numCols);
    Matrix();
    Matrix operator+(const Matrix& other) const;
    Matrix hadamard(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(const float scalar) const;
    // ~Matrix();
    // testing git
    // Instance Fields
    std::vector<std::vector<double>> data;
    size_t rows;
    size_t cols;
};
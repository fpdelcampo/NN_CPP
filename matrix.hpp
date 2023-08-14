#pragma once

#include <vector>

// Eventually, this should deal with generic numeric types (i.e, ints, doubles, floats, etc)

class Matrix{
public:
    Matrix(size_t num_rows, size_t num_cols, std::vector<std::vector<double>> data);
    Matrix(size_t num_rows, size_t num_cols);
    Matrix();
    Matrix(double vec_data[], size_t len_vec, bool row_vec);
    Matrix transpose() const;
    static Matrix identity(size_t rows, size_t cols);
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(const float scalar) const;
    Matrix hadamard(const Matrix& other) const;
    // ~Matrix();
    // testing git
    // Instance Fields
    std::vector<std::vector<double>> data;
    size_t rows;
    size_t cols;
};
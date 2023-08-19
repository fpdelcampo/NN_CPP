#pragma once

#include <vector>

// Eventually, this should deal with generic numeric types (i.e, ints, doubles, floats, etc)

class Matrix{
public:
    size_t rows;
    size_t cols;
    std::vector<std::vector<double>> data;

    Matrix(size_t num_rows, size_t num_cols, std::vector<std::vector<double>> data);
    Matrix(size_t num_rows, size_t num_cols);
    Matrix();
    Matrix(double vec_data[], size_t len_vec, bool row_vec);
    Matrix(std::vector<double> vec_data, size_t len_vec, bool row_vec);
    Matrix transpose() const;
    static Matrix identity(size_t rows, size_t cols);
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(const double scalar) const;
    Matrix hadamard(const Matrix& other) const;
    Matrix ReLU() const;
    Matrix dRelu() const;
    Matrix uniform_initialization();
    Matrix submatrix(int top, int left, int bottom, int right, bool include) const;

    // ~Matrix();
    // testing git
    // Instance Fields
    
};
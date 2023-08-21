#pragma once

#include <vector>

class SMatrix{
    public:
        size_t rows;
        size_t cols;
        std::vector<double> data;
        SMatrix(size_t num_rows, size_t num_cols, std::vector<double> data);
        SMatrix(size_t num_rows, size_t num_cols);
        SMatrix transpose() const;
        SMatrix identity(size_t rows, size_t cols) const;
        SMatrix operator+(const SMatrix& other) const;
        SMatrix operator-(const SMatrix& other) const;
        SMatrix operator*(const SMatrix& other) const;
        SMatrix operator*(const double scalar) const;
        SMatrix hadamard(const SMatrix& other) const;
        static SMatrix strassen(const SMatrix& A, const SMatrix& B);
};
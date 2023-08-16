#pragma once

#include <vector>

class SMatrix{
public:
    SMatrix(size_t num_rows, size_t num_cols, std::vector<double> data);
    SMatrix operator+(const SMatrix& other) const;
    SMatrix operator-(const SMatrix& other) const;
    SMatrix operator*(const SMatrix& other) const;
    SMatrix operator*(const float scalar) const;
}
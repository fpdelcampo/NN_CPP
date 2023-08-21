#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <stdexcept>
#include "simple_matrix.hpp"

// We really should use a "flattened" 1-d vector to represent the data in the matrix
// https://stackoverflow.com/questions/17259877/1d-or-2d-array-whats-faster
// Can worry about this later since it's a simple optimization

SMatrix::SMatrix(size_t num_rows, size_t num_cols, std::vector<double> d) { // again, if the last arguments name is data, we get segfaults for some reason
    rows = num_rows;
    cols = num_cols;
    data = d;
} 

SMatrix::SMatrix(size_t num_rows, size_t num_cols) {
    rows = num_rows;
    cols = num_cols;
    std::vector<double> zeros(num_rows*num_cols, 0);
    data = zeros;
}
// 5x4
// I want [2][0]; 9th element, so index is 8
// Can make this faster by only visiting the elements along the diagonal and above it
SMatrix SMatrix::transpose() const {
    SMatrix mat = SMatrix(cols, rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++ ) {
            mat.data[j*cols+i] = data[i*cols+j];
        }
    }
    return mat;
}
// In 4x4; 0, 5, 10, 15
SMatrix SMatrix::identity(size_t rows, size_t cols) const {
    if(rows != cols) {
        throw std::invalid_argument("Dimensions of arrays must match"); 
    }
    SMatrix result(rows, cols);
    for(int i = 0; i<rows; i++) {
        result.data[i*cols+i] = 1;
    }
    return result;
}
// is there a more efficient way where we directly overwrite data

SMatrix SMatrix::operator+(const SMatrix& other) const {
    if(rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Dimensions of arrays must match"); 
    }

    // std::vector<std::vector<double>> new_vector;
    // new_vector.resize(rows, std::vector<double>(cols, 0));
    SMatrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[j*cols+i] = data[j*cols+i] + other.data[j*cols+i];
        }
    }
    return result;
}

SMatrix SMatrix::operator-(const SMatrix& other) const {
    if(rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Dimensions of arrays must match"); 
    }
    SMatrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[j*cols+i] = data[j*cols+i] +- other.data[j*cols+i];
        }
    }
    return result;
}

SMatrix SMatrix::operator*(const SMatrix& other) const {
    if(cols != other.rows) {
        throw std::invalid_argument("Dimensions of arrays must match"); 
    }

    SMatrix result(rows, other.cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.cols; j++ ) {
            for (int k = 0; k < cols; k++ ) {
                result.data[j*cols+i] += data[k+cols+i]*other.data[j*cols+k];
            }
        }
    }
    return result;
}

SMatrix SMatrix::operator*(const double scalar) const {
    SMatrix result(rows, cols);
    for(int i = 0; i<rows*cols; i++) {
        result.data[i] = scalar*data[i];
    }
    return result;
}
// Matrix is 4 x 5
// Want to access cell 3, 2
// This corresponds to 5x3+2 or 

SMatrix SMatrix::hadamard(const SMatrix& other) const {
    if(rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Dimensions of arrays must match"); 
    }
    SMatrix result(rows, cols);
    for (int i = 0; i < rows*cols; i++) {
        result.data[i] = data[i] * other.data[i];
    }
    return result;
}

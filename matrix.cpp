#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <stdexcept>
#include "matrix.hpp"
#include <random>

// We really should use a "flattened" 1-d vector to represent the data in the matrix
// https://stackoverflow.com/questions/17259877/1d-or-2d-array-whats-faster
// Can worry about this later since it's a simple optimization

Matrix::Matrix(size_t num_rows, size_t num_cols, std::vector<std::vector<double>> d) { // again, if the last arguments name is data, we get segfaults for some reason
    rows = num_rows;
    cols = num_cols;
    data = d;
} 
Matrix::Matrix(size_t num_rows, size_t num_cols) {
    rows = num_rows;
    cols = num_cols;
    std::vector<std::vector<double>> d(rows, std::vector<double>(cols, 0));
    data = d;
} 
Matrix::Matrix() {
   rows = 1;
   cols = 1;
   std::vector<std::vector<double>> d(1, std::vector<double>(1, 0)); // if you call this variable d, you get errors for some reason
   data = d; 
}
Matrix::Matrix(double vec_data[], size_t len_vec, bool row_vec=true) {
    std::vector<double> convert((double *)vec_data, (double *)vec_data+len_vec); // this wraps the array into a vector
    // If row_vec, we need to make the vector 1xn
    // otherwise, we need to make the vector nx1

    std::vector<std::vector<double>> vec(1, convert);
    
    if(row_vec) {
        data.push_back(convert);
        rows = 1;
        cols = len_vec;
    }
    else {
        for (size_t i = 0; i < len_vec; ++i) {
            data.push_back(std::vector<double>{convert[i]});
        }
        rows = len_vec;
        cols = 1;
    }
}
Matrix::Matrix(std::vector<double> vec_data, size_t len_vec, bool row_vec=true) {
    // std::vector<double> convert(vec_data,vec_data+len_vec); // this wraps the array into a vector
    // If row_vec, we need to make the vector 1xn
    // otherwise, we need to make the vector nx1

    std::vector<std::vector<double>> vec(1, vec_data);
    
    if(row_vec) {
        data = vec;
        rows = 1;
        cols = len_vec;
    }
    else {
        for (size_t i = 0; i < len_vec; ++i) {
            data.push_back(std::vector<double>{vec_data[i]});
        }
        rows = len_vec;
        cols = 1;
    }
}
// gave errors for some reason, something about a non-void function
/* Matrix Matrix::transpose() {
    for (int i = 0; i < rows; i++) {
        for (int j = i; j < cols; j++ ) {
            double tmp = data[i][j];
            data[i][j] = data[j][i];
            data[j][i] = tmp;
        }
    }
} */


// maybe can make inplace options for this function and others
Matrix Matrix::transpose() const {
    Matrix mat = Matrix(cols, rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++ ) {
            mat.data[j][i] = data[i][j];
        }
    }
    return mat;
}

Matrix Matrix::identity(size_t rows, size_t cols) {
    if(rows != cols) {
        throw std::invalid_argument("Dimensions of arrays must match"); 
    }
    Matrix result(rows, cols);
    for(int i = 0; i<rows; i++) {
        result.data[i][i] = 1;
    }
    return result;
}
// is there a more efficient way where we directly overwrite data

Matrix Matrix::operator+(const Matrix& other) const {
    if(rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Dimensions of arrays must match"); 
    }

    // std::vector<std::vector<double>> new_vector;
    // new_vector.resize(rows, std::vector<double>(cols, 0));
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    if(rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Dimensions of arrays must match"); 
    }
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;
}

// See the following for speedup ideas: https://stackoverflow.com/questions/4300663/how-to-speed-up-matrix-multiplication-in-c
// Use strassen for square matrices both with the same dimensions and whose dimensions are powers of 2
// Explore free operators so the order doesn't matter
// Read this: https://chryswoods.com/vector_c++/immintrin.html
// Maybe also this: https://developer.arm.com/documentation/den0018/a/NEON-Intrinsics/Using-NEON-intrinsics
Matrix Matrix::operator*(const Matrix& other) const {
    if(cols != other.rows) {
        throw std::invalid_argument("Dimensions of arrays must match"); 
    }

    Matrix result(rows, other.cols);

    // matmul logic

    // rows, cols = other.rows, other.cols
    // c= a*b
    // c[i][j] = ith row of a __dot product__ jth col of b
    // c[i][j] += kth element of ith row of a + kth element of jth col of b

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.cols; j++ ) {
            for (int k = 0; k < cols; k++ ) {
                result.data[i][j] += data[i][k]*other.data[k][j];
            }
        }
    }
    return result;
}

Matrix Matrix::operator*(const double scalar) const {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++ ) {
            result.data[i][j] = data[i][j] * scalar;
        }
    }
    return result;
}

Matrix Matrix::hadamard(const Matrix& other) const {
    if(rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Dimensions of arrays must match"); 
    }

    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++ ) {
            result.data[i][j] = data[i][j] * other.data[i][j];
        }
    }
    return result;
}
Matrix Matrix::ReLU() const {
    Matrix result(rows, cols);
    for(int i = 0; i<rows; i++) {
        for(int j = 0; j<cols; j++){
            result.data[i][j] = result.data[i][j] > 0 ? result.data[i][j] : 0;
        }
    }
    return result;
}
Matrix Matrix::dRelu() const {
    Matrix result(rows, cols);
    for(int i = 0; i<rows; i++) {
        for(int j = 0; j<cols; j++){
            result.data[i][j] = result.data[i][j] > 0 ? 1 : 0;
        }
    }
    return result;
}

void Matrix::uniform_initialization() {
    std::random_device rd;    // Seed the random number generator
    std::mt19937 gen(rd());   // Mersenne Twister engine for random numbers

    double minRange = -.1;        // Minimum value of the range
    double maxRange = .1;        // Maximum value of the range

    std::uniform_int_distribution<int> dist(minRange, maxRange);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            data[i][j] = dist(gen);
        }
    }
}

Matrix Matrix::submatrix(int top, int left, int bottom, int right, bool include) const{
    if(left > right) {
        throw std::invalid_argument("Dimensions of arrays must match"); 
    }
    if(bottom < top) {
        throw std::invalid_argument("Dimensions of arrays must match"); 
    }
    if(rows <= bottom) {
        throw std::invalid_argument("Dimensions of arrays must match"); 
    }
    if(cols <= right) {
        throw std::invalid_argument("Dimensions of arrays must match"); 
    }
    if(include) {
        bottom+=1;
        right+=1;
    }
    std::vector<std::vector<double>> new_data;
    for(int i=top;i<bottom; i++) {
        std::vector<double> row;
        for(int j=left; j<right;j++) {
            row.push_back(data[i][j]);
        }
        new_data.push_back(row);
    }
    return Matrix(right-left, bottom-top, new_data);
}

// Matrix Matrix::vec_mul(const std::vector vec) const {
//     Matrix result(rows, cols);
//     for (int i = 0; i < rows; i++) {
//         for (int j = 0; j < cols; j++ ) {
//             result.data[i][j] = data[i][j] * scalar;
//         }
//     }
//     return result;
// }

// Matrix Matrix::arr_mul(const float scalar) const {
//     Matrix result(rows, cols);
//     for (int i = 0; i < rows; i++) {
//         for (int j = 0; j < cols; j++ ) {
//             result.data[i][j] = data[i][j] * scalar;
//         }
//     }
//     return result;
// }
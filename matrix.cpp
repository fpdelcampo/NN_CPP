#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <stdexcept>
#include "matrix.hpp"


// class Matrix {
//     private:
//         std::vector<std::vector<double>> data;
//         size_t rows;
//         size_t cols;

//     public:
//         // put check to ensure no negative dimensions 
//         Matrix(size_t numRows, size_t numCols) : rows(numRows), cols(numCols), data(numRows, std::vector<double>(numCols, 0.0)) {}
//         Matrix() : rows(1), cols(1), data(1, std::vector<double>(1, 0)) {}

//         // is there a more efficient way where we directly overwrite data

//         Matrix operator+(const Matrix& other) const {
//             if(rows != other.rows || cols != other.cols) {
//                 throw std::invalid_argument("Dimensions of arrays must match"); 
//             }

//             // std::vector<std::vector<double>> new_vector;
//             // new_vector.resize(rows, std::vector<double>(cols, 0));
//             Matrix result(rows, cols);
//             for (int i = 0; i < rows; i++) {
//                 for (int j = 0; j < cols; j++) {
//                     result.data[i][j] = data[i][j] + other.data[i][j];
//                 }
//             }
//             return result;
//         }
        
//         Matrix hadamard(const Matrix& other) const {
//             if(rows != other.rows || cols != other.cols) {
//                 throw std::invalid_argument("Dimensions of arrays must match"); 
//             }

//             Matrix result(rows, cols);
//             for (int i = 0; i < rows; i++) {
//                 for (int j = 0; j < cols; j++ ) {
//                     result.data[i][j] = data[i][j] * other.data[i][j];
//                 }
//             }
//             return result;
//         }

//         Matrix operator*(const Matrix& other) const {
//             if(cols != other.rows) {
//                 throw std::invalid_argument("Dimensions of arrays must match"); 
//             }

//             Matrix result(rows, other.cols);

//             // matmul logic

//             // rows, cols = other.rows, other.cols
//             // c= a*b
//             // c[i][j] = ith row of a __dot product__ jth col of b
//             // c[i][j] += kth element of ith row of a + kth element of jth col of b

//             for (int i = 0; i < rows; i++) {
//                 for (int j = 0; j < other.cols; j++ ) {
//                     for (int k = 0; k < cols; k++ ) {
//                         result.data[i][j] += data[i][k]*other.data[k][j];
//                     }
//                 }
//             }
//             return result;
//         }

//         Matrix operator*(const float scalar) const {
//             Matrix result(rows, cols);
//             for (int i = 0; i < rows; i++) {
//                 for (int j = 0; j < cols; j++ ) {
//                     result.data[i][j] = data[i][j] * scalar;
//                 }
//             }
//             return result;
//         }
// };


Matrix::Matrix(size_t numRows, size_t numCols) : rows(numRows), cols(numCols), data(numRows, std::vector<double>(numCols, 0.0)) {}
Matrix::Matrix() : rows(1), cols(1), data(1, std::vector<double>(1, 0)) {}

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

Matrix Matrix::operator*(const float scalar) const {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++ ) {
            result.data[i][j] = data[i][j] * scalar;
        }
    }
    return result;
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
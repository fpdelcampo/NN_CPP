#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "Matrix.hpp"
#include "dense.hpp"


Dense::Dense(size_t in, size_t out) {
    in_shape = in;
    out_shape = out;
    weights = Matrix(out, in);
    biases = Matrix(out, 1);
    gradient_weights = Matrix(out, in);
    gradient_biases = Matrix(out, 1);
    output = Matrix(out, 1);
    // learning_rate = lr;
}

void Dense::forward(Matrix mat) {
    // A = Wx+b
    input = mat;
    Matrix A = weights*input+biases;
    A = A.ReLU();
    output = A;
}

// https://en.wikipedia.org/wiki/Backpropagation
Matrix backward(Matrix mat, double lr) {
    // da/dz
    Matrix da_dz = Matrix.identity(out_shape, out_shape)
    for (int i = 0; i < out_shape; i++) {
        da_dz[i][i] = output.data[i][1] > 0 > 1 : 0;
    }

    // dz/dW and dz/db
    Matrix dz_dW(out_shape, in_shape * out_shape);
    Matrix dz_db = Matrix.identity(out_shape, out_shape);
    for (int i = 0; i < out_shape; i++) {
        for (int j = 0; j < in_shape; j++) {
            dz_dW[i][i * in_shape + j] = input.data[j][1];
        }
    }

    // gradient computation
    Matrix grad_weights = mat * da_dz * dz_dW;
    Matrix grad_biases = mat * da_dz * dz_db;

    // Apply gradients to weights and biases
    for (int i = 0; i < out_shape; i++) {
        for (int j = 0; j < in_shape; j++) {
            weights[i][j] = weights[i][j] - grad_weights.data[i * in_shape + j] * lr;
        }
        biases[i] = biases[i] - grad_biases[i] * lr;
    }

    // Return da/dz * dz/da(l-1)
    return mat * da_dz * weights;

    
}
// Matrix uniform_initialization(Matrix mat) {
//     for (int i = 0; i < mat.rows; i++) {
//         for (int j = 0; j < mat.cols; j++) {
            
//         }
//     }
// }

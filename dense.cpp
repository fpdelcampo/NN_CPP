#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "matrix.hpp"
#include "dense.hpp"


Dense::Dense(size_t in, size_t out) {
    in_shape = in;
    out_shape = out;
    weights = Matrix(out, in);
    biases = Matrix(out, 1);
    gradient_weights = Matrix(out, in);
    gradient_weights.uniform_initialization();
    gradient_biases = Matrix(out, 1);
    gradient_biases.uniform_initialization();
    input = Matrix(in, 1);
    intermediary = Matrix(out, 1);
    output = Matrix(out, 1);
    calls = 0;
    // learning_rate = lr;
}

void Dense::forward(Matrix mat) {
    // A = Wx+b
    input = mat;
    intermediary = weights*input+biases;
    Matrix A = intermediary.ReLU();
    output = A;
}

// https://en.wikipedia.org/wiki/Backpropagation
Matrix Dense::backward(Matrix mat, double lr) {
    // If this is the layer 2, then we have dC/da_2 as mat
    Matrix dz = mat.hadamard(intermediary.dRelu()); // out x 1 .* out x 1
    Matrix dW = dz*input.transpose(); // out x 1 * 1 x in
    Matrix db = dz;
    gradient_weights = gradient_weights + dW * lr;
    gradient_biases = gradient_biases + db * lr;
    calls += (double) 1;
    return weights.transpose() * dz; // in x out * out * 1
}

void Dense::update() {
    weights = weights - gradient_weights * (1./calls);
    biases = biases - gradient_biases*(1./calls);
    gradient_weights = Matrix(out_shape, in_shape);
    gradient_biases = Matrix(out_shape, 1);
    calls = 0;
}

// Matrix backward(Matrix mat, double lr) {
//     // We have mat = dC / da
//     // da/dz
//     Matrix da_dz = Matrix.identity(out_shape, out_shape)
//     for (int i = 0; i < out_shape; i++) {
//         da_dz.data[i][i] = output.data[i][1] > 0 > 1 : 0;
//     }

//     // dz/dW and dz/db
//     Matrix dz_dW(out_shape, in_shape * out_shape);
//     Matrix dz_db = Matrix.identity(out_shape, out_shape);
//     for (int i = 0; i < out_shape; i++) {
//         for (int j = 0; j < in_shape; j++) {
//             dz_dW.data[i][i * in_shape + j] = input.data[j][1];
//         }
//     }

//     // gradient computation
//     Matrix grad_weights = mat * da_dz * dz_dW;
//     Matrix grad_biases = mat * da_dz * dz_db;

//     // Apply gradients to weights and biases
//     for (int i = 0; i < out_shape; i++) {
//         for (int j = 0; j < in_shape; j++) {
//             weights.data[i][j] = weights[i][j] - grad_weights.data[i * in_shape + j] * lr;
//         }
//         biases[i] = biases[i] - grad_biases[i] * lr;
//     }

//     // Return da/dz * dz/da(l-1)
//     return mat * da_dz * weights;

    
// }
// Matrix uniform_initialization(Matrix mat) {
//     for (int i = 0; i < mat.rows; i++) {
//         for (int j = 0; j < mat.cols; j++) {
            
//         }
//     }
// }

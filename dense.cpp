#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "Matrix.hpp"
#include "dense.hpp"


Dense::Dense(size_t in, size_t out, double lr) {
    in_shape = in;
    out_shape = out;
    weights = Matrix(out, in);
    biases = Matrix(out, 1);
    gradient_weights = Matrix(out, in);
    gradient_biases = Matrix(out, 1);
    output = Matrix(out, 1);
    learning_rate = lr;
}

void Dense::forward(Matrix mat) {
    // A = Wx+b
    Matrix A = weights*mat+biases;
    A = A.ReLU();
    output = A;
}

// https://en.wikipedia.org/wiki/Backpropagation
void backward(Matrix mat) {
    Matrix d_l = output.transpose()*mat;

    
}
// Matrix uniform_initialization(Matrix mat) {
//     for (int i = 0; i < mat.rows; i++) {
//         for (int j = 0; j < mat.cols; j++) {
            
//         }
//     }
// }

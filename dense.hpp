#pragma once

#include "matrix.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>


class Dense {
    public:
        // need to have input and output shapes, weights, biases, activation function, gradients for w and b
        size_t in_shape;
        size_t out_shape;
        Matrix weights;
        Matrix biases;
        Matrix gradient_weights;
        Matrix gradient_biases;  
        Matrix output;
        Matrix input;
        double learning_rate;
        
        Dense(size_t in, size_t out, double lr);
        void forward(Matrix mat);
        void backward(Matrix mat);
        // Matrix uniform_initialization(Matrix mat);
};
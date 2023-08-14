#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "Matrix.hpp"


class Dense {
    public:
        // need to have input and output shapes, weights, biases, activation function, gradients for w and b
        size_t in_shape;
        size_t out_shape;
        Matrix weights;
        Matrix biases;
        Matrix gradient_weights;
        Matrix gradient_biases;
        Matrix forward(Matrix);  
        Matrix (activation)(Matrix);




};

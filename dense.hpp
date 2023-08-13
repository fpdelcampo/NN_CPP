#pragma once

#include "matrix.hpp"

class dense{
public:
    size_t in_shape;
        size_t out_shape;
        Matrix weights;
        Matrix biases;
        Matrix gradient_weights;
        Matrix gradient_biases;
};
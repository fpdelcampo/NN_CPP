#pragma once
#include "dense.hpp"
#include <vector>

class FeedForward {

    // think of return type if we need it
    // const here indicates that the function is not modifying the state of the object calling the method
    public:
        std::vector<Dense> layers;
        double learning_rate;
        FeedForward();
        FeedForward(std::vector<int> layer_sizes, double lr);
        FeedForward(std::vector<Dense> layers, double lr);
        void forward(Matrix in);
        void backward(Matrix y, Matrix y_pred);
        void update();
        void train(Matrix X, Matrix y, int batch_size, int epochs);
};
#include "feedforward.hpp"
#include "dense.hpp"
#include <vector>

FeedForward::FeedForward(std::vector<Dense> layers, double lr) {
    layers = layers;
    learning_rate = lr;
}

FeedForward::FeedForward(std::vector<int> layer_sizes, double lr) {
    learning_rate = lr;
    for (int i = 0; i < layer_sizes.size() - 1; i++) {
        layers.push_back(Dense(layer_sizes[i], layer_sizes[i + 1]));
    }
}

FeedForward::FeedForward() { // again, if the last arguments name is data, we get segfaults for some reason
    layers.push_back(Dense(2, 3));
    layers.push_back(Dense(3, 1));
    learning_rate = 0.001;
}

void FeedForward::forward(Matrix in) {
    for(int i = 0; i < layers.size(); i++) {
        layers[i].forward(in);
        in = layers[i].output;
    }
}

void FeedForward::backward(Matrix y, Matrix y_pred) {
    double factor = double (1)/ double (y.rows);
    Matrix mat = (y_pred - y) * factor;
    for (int i = layers.size() - 1; i >= 0; i--) {
        mat = layers[i].backward(mat, learning_rate);
    }
}

void FeedForward::update() {
    for(int i = 0; i < layers.size(); i++) {
        layers[i].update();
    }
}

void FeedForward::train(Matrix X, Matrix y, int batch_size, int epochs) {
    for(int epoch = 0; epoch<epochs; epoch++) {

        // input = 1000 x N
        // batch size = 10; take 10 100 x N
        
        for (int i = 0; i < X.rows; i++) {
            forward(Matrix(X.data[i], X.cols, false));
            backward(Matrix(y.data[i], y.cols, false), layers[layers.size() - 1].output); 
            update();
        }
    }
    
        

        
}


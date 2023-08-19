#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "matrix.hpp"
#include "feedforward.hpp"

int main() {
    // 1000 x1*x2
    // X -> h -> y will never be < 0
    Matrix X = Matrix(1000, 2);
    X.uniform_initialization();
    Matrix y = Matrix(1000,1);
    for(int i=0; i<1000;i++) {
        y.data[i][0] = X.data[i][0] + X.data[i][1]; // can be < 0
    }
    FeedForward f = FeedForward();
    f.train(X, y, 1, 10);
}
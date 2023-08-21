#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "matrix.hpp"
#include "simple_matrix.hpp"
#include <chrono>

int main() {
    // size_t rows = 2;
    // size_t cols = 2;
    // std::vector<std::vector<double>> data;
    Matrix test = Matrix();
    printf("asdfhk");
    printf("\n");
    std::cout << test.data[0][0];

    Matrix test2 = Matrix::identity(3, 3);
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++) {
            std::cout << test2.data[i][j];
        }
        std::cout << std::endl;
    }

    Matrix test3 = Matrix(3, 3);
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++) {
            std::cout << test3.data[i][j];
        }
        std::cout << std::endl;
    }
    
    float scalar = 2.0;
    Matrix test4 = test2*scalar;
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++) {
            std::cout << test4.data[i][j];
        }
        std::cout << std::endl;
    }
    Matrix test5 = test4-test2;

    Matrix test6 = test2*test4;
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++) {
            std::cout << test6.data[i][j];
        }
        std::cout << std::endl;
    }
    
    double arr1[2] = {1, 2};
    double arr2[2] = {3, 4};

    std::vector<std::vector<double>> two_d_vector;

    for (int i = 0; i < 2; ++i) {
        std::vector<double> row;
        row.push_back(arr1[i]);
        row.push_back(arr2[i]);
        two_d_vector.push_back(row);
    }

    
    printf("\n");
    Matrix test7 = Matrix(2, 2, two_d_vector);
    for(int i=0; i<2; i++){
        for(int j=0; j<2; j++) {
            std::cout << test7.data[i][j];
        }
        std::cout << std::endl;
    }
    printf("\n");
    
    Matrix test8 = test7.transpose();
    for(int i=0; i<2; i++){
        for(int j=0; j<2; j++) {
            std::cout << test8.data[i][j];
        }
        std::cout << std::endl;
    }

    std::vector<std::vector<double>> data1;
    std::vector<std::vector<double>> data2;

    std::vector<double> data3;
    std::vector<double> data4;

    for(int i=0; i<512; i++) {
        std::vector<double> row1;
        std::vector<double> row2;
        for(int j=0; j<512; j++) {
            row1.push_back(i);
            row2.push_back(-i);
            data3.push_back(i*j);
            data4.push_back(-i-j);
        }
        data1.push_back(row1);
        data2.push_back(row2);
    }
    
    // From tests, multiplication of two 512 x 512 matrices takes 0.75 seconds

    Matrix test9 = Matrix(512, 512, data1);
    Matrix test10 = Matrix(512, 512, data2);
    SMatrix test11 = SMatrix(512, 512, data3);
    SMatrix test12 = SMatrix(512, 512, data4);

    auto start = std::chrono::high_resolution_clock::now();
    Matrix test13 = test9*test10;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;

    auto start2 = std::chrono::high_resolution_clock::now();
    SMatrix test14 = test11*test12;
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration2 = end2 - start2;
    std::cout << "Time taken: " << duration2.count() << " seconds" << std::endl;

    return 0;


}

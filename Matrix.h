//
// Created by dawid on 27.12.2019.
//

#ifndef GENETICALGORITHM_MATRIX_H
#define GENETICALGORITHM_MATRIX_H

#include <vector>
#include <string>
#include "fstream"
#include <iostream>

class Matrix {
    std::string matrixName;

    int matrixSize;

    int **matrix;

    int *shortestPath;

public:
    int *const &operator[](int) const;

    Matrix(std::string, std::string);

    ~Matrix();

    std::string getName();

    int getMatrixSize() const;

    void printMatrix();

    int pathValue(std::vector<int>) const;
};


#endif //GENETICALGORITHM_MATRIX_H

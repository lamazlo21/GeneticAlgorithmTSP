//
// Created by dawid on 27.12.2019.
//

#include "Matrix.h"

using namespace std;

Matrix::~Matrix() {
    delete [] matrix;
    delete [] shortestPath;
}

Matrix::Matrix(string fileName, string filePath) {

    ifstream file;
    file.open(filePath+fileName, ios::out);
    file >> matrixName;
    file >> matrixSize;
    shortestPath = new int[matrixSize];
    if(file.is_open()){
        matrix = new int*[matrixSize];
        for(int i=0; i<matrixSize; i++) {
            shortestPath[i] = 0;
            matrix[i] = new int[matrixSize];
            for (int j = 0; j < matrixSize; j++)
                file >> matrix[i][j];
        }
        file.close();
    }
    else{
        cout<<"File cannot be opened!"<<endl;
    }
}

void Matrix::printMatrix() {

    for(int i=0; i<matrixSize;i++){
        for(int j=0; j<matrixSize; j++)
            cout<<matrix[i][j]<<" ";
        cout<<endl;
    }
}

int Matrix::getMatrixSize() const {
    return matrixSize;
}

std::string Matrix::getName() {
    return matrixName;
}

int* const &Matrix::operator[](int i) const{
    return matrix[i];
}

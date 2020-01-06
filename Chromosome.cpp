//
// Created by dawid on 27.12.2019.
//

#include "Chromosome.h"

using namespace std;

Chromosome:: Chromosome(std::vector<int> genes, const Matrix& matrix) : genes(genes){
    calcValue(matrix);
}

bool Chromosome::operator<(const Chromosome &chromosome) const {
    return _value < chromosome._value;
}

void Chromosome::calcValue(const Matrix& matrix){
    int min = 0;
    for(int i=0; i<genes.size()-1; i++)
        min += matrix[genes[i]][genes[i + 1]];
    min+=matrix[genes[genes.size()-1]][0];
    _value = min;
}

void Chromosome::calcFitness(int factor) {
    _fitness = (float)_value/(float)factor;
}

void Chromosome::printChromosome() const{
    cout<<"Chromosom: ";
    for(int i=0; i<genes.size(); i++)
        cout<<genes[i]<<" ";
    cout<<"Fitnes: "<<_value<<endl;
}

int Chromosome::fitness() const{
    return _fitness;
}

int Chromosome::value() const{
    return _value;
}
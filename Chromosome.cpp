//
// Created by dawid on 27.12.2019.
//

#include "Chromosome.h"

using namespace std;

Chromosome:: Chromosome(std::vector<int> genes) : genes(genes){
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
    for(int i=0; i<genes.size(); i++)
        cout<<genes[i]<<" ";
    cout<<endl;
}

int Chromosome::fitness(){
    return _fitness;
}
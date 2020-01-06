//
// Created by dawid on 27.12.2019.
//

#ifndef GENETICALGORITHM_CHROMOSOME_H
#define GENETICALGORITHM_CHROMOSOME_H

#include <vector>
#include <iostream>
#include "Matrix.h"

class Chromosome{
    friend class Genetic;
    std::vector<int> genes;
    float _fitness;
    int _value;

public:
    bool operator < (const Chromosome& chromosome) const;
    Chromosome(std::vector<int> genes, const Matrix& matrix);
    void calcValue(const Matrix& matrix);
    void calcFitness(int factor);
    void printChromosome() const;
    int fitness() const;
    int value() const;
};

#endif //GENETICALGORITHM_CHROMOSOME_H

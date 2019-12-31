//
// Created by dawid on 27.12.2019.
//

#ifndef GENETICALGORITHM_GENETICALGORITHM_H
#define GENETICALGORITHM_GENETICALGORITHM_H

#include <vector>
#include <iostream>
#include "Chromosome.h"
#include "Matrix.h"
#include <random>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <cstdlib>

class Genetic{
    const Matrix& matrix;
    std::vector<Chromosome> population;
    bool findInRange(Chromosome& first, Chromosome& second, int start, int end, int gene) const;
public:
    Genetic(const Matrix &matrix);
    void printPopulation() const;
    void initializePopulation(int size);
    void rankPopulation();
    void rankSelection(int eliteSize);
    void tournamentSelection(int eliteSize);
    void crossover();
    void mutate();

};

#endif //GENETICALGORITHM_GENETICALGORITHM_H

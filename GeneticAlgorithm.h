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
    void rankSelection(int eliteSize);
    Chromosome tournamentSelection(int tournamentSize);
    void crossover(Chromosome& first, Chromosome& second) const;
    void mutate(double mutationRate, Chromosome& chromosome) const;
    void nextGenerationTournament(int eliteSize, int tournamentSize, double mutationRate);

public:
    Genetic(const Matrix &matrix);
    void initializePopulation(int populationSize, int chromosomeSize);
    void printPopulation() const;
    Chromosome geneticAlgorithm(int populationSize, int chromosomeSize, int eliteSize,  int tournamentSize, double mutationRate, int generations);
};

#endif //GENETICALGORITHM_GENETICALGORITHM_H

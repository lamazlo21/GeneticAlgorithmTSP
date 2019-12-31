#include <iostream>
#include "GeneticAlgorithm.h"
#include "Matrix.h"

using namespace std;

int main() {
    Matrix matrix{"data10.txt", "../DATA/SYM/"};
    Genetic genetic(matrix);

    genetic.initializePopulation(10);
    genetic.rankPopulation();
    genetic.rankSelection(2);
    genetic.crossover();

    return 0;
}

#include <iostream>
#include "GeneticAlgorithm.h"
#include "Matrix.h"
#include <ctime>
#include <cstdlib>

using namespace std;

int main() {
    srand(time(NULL));
    Matrix matrix{"data10.txt", "../DATA/SYM/"};
    Genetic genetic(matrix);

    double mutationRate = 0.1;
    int eliteSize = 10, populationSize = 1000, chromosomeSize = matrix.getMatrixSize(), generations = 1000, tournamentSize = 2;
    Chromosome result = genetic.geneticAlgorithm(populationSize, chromosomeSize, eliteSize, tournamentSize, mutationRate, generations);
    cout<<"Wynik: "<<result.value()<<endl;
    return 0;
}

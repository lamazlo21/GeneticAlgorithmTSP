//
// Created by dawid on 27.12.2019.
//

#include "GeneticAlgorithm.h"

using namespace::std;

random_device rd;
mt19937 generator(rd());
uniform_real_distribution<double> distribution(0.0,1.0);

Genetic::Genetic(const Matrix &matrix) : matrix(matrix){

}

bool Genetic::findInRange(Chromosome& first, Chromosome& second, int start, int end, int gene) const {
    for(int i=start; i<=end; i++)
        if(second.genes[gene] == first.genes[i])
            return true;
    return false;
}

void Genetic::initializePopulation(int size) {
    unsigned seed;
    vector<int> genes;
    for(int i=0; i<size; i++){
        genes.push_back(i);
    }
    for(int i=0; i<size; i++){
        // Tworzenie populacji początkowej za pomocą funkcji shuffle
        seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle(genes.begin()+1, genes.end(), default_random_engine(seed));
        Chromosome chromosome{genes};
        chromosome.calcValue(matrix);
        population.push_back(chromosome);
    }
}

void Genetic::rankPopulation() {
    int factor = 0;
    for(int i=0; i<population.size(); i++)
        factor += population[i]._value;
    for(int i=0; i<population.size(); i++)
        population[i].calcFitness(factor);
    sort(population.begin(), population.end(), [](Chromosome& a, Chromosome& b) -> bool{
        return a._value > b._value;
    });
}

void Genetic::rankSelection(int eliteSize) {
    int factor = 0;
    double range = 0;
    vector<double> ranges;
    vector<Chromosome> pool;
    rankPopulation();
    for(int i=0; i<population.size(); i++)
        factor += i+1;
    for(int i=0; i<population.size(); i++){
        ranges.push_back(range + (double)(i+1)/(double)factor);
        range = ranges[i];
    }
    for(int i=population.size()-1; i>population.size()-1-eliteSize; i--)
        pool.push_back(population[i]);
    double number;
    for(int i=population.size()-1-eliteSize; i>=0; i--) {
        number = distribution(generator);
        for(int j=0; j<population.size(); j++)
            if(number<=ranges[j]) {
                pool.push_back(population[j]);
                break;
            }
    }
    population = pool;
}

void Genetic::crossover() {
    srand(time(NULL));
    int start, end;
    int chromosomeSize = population[0].genes.size();
    vector<int> offspring;
    vector<Chromosome> offsprings;
    for(int i=0; i<population.size(); i++) {
        start = rand() % (population.size() - 2)+1;
        end = rand() % (population.size() - start) + start;
        offspring.push_back(0);
        for(int j=1; j<chromosomeSize; j++)
            if (!findInRange(population[i], population[chromosomeSize - 1 - i], start, end, j))
                offspring.push_back(population[chromosomeSize - 1 - i].genes[j]);
        if(offspring.size() == start)
            for(int k=start; k<=end; k++)
                offspring.push_back(population[i].genes[k]);
        else
            for(int k=start; k<=end; k++)
                offspring.insert(offspring.begin()+k, population[i].genes[k]);
        Chromosome chromosome{offspring};
        offsprings.push_back(chromosome);
        offspring.clear();
    }
    population = offsprings;
}

void Genetic::mutate() {

}

void Genetic::printPopulation() const{
    for(Chromosome chromosome : population)
        chromosome.printChromosome();
}
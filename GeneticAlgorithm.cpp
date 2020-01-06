//
// Created by dawid on 27.12.2019.
//

#include "GeneticAlgorithm.h"

using namespace::std;

random_device rd;
mt19937 generator(rd());

Genetic::Genetic(const Matrix &matrix) : matrix(matrix){

}

void Genetic::crossover(Chromosome& first, Chromosome& second) const {
    uniform_int_distribution<int>  firstInt(1, first.genes.size() - 2);
    int start = firstInt(generator);
    uniform_int_distribution<int>  secondInt(start + 1, first.genes.size() - 1);
    int end = secondInt(generator);
    vector<int> firstChild, secondChild;
    for(int i=0; i<first.genes.size(); i++) {
        int firstGene = first.genes[i];
        int secondGene = second.genes[i];
        int firstCounter = 0, secondCounter = 0;
        for (int j = start; j <= end; j++) {
            if (firstGene == second.genes[j])
                firstCounter++;
            if (secondGene == first.genes[j])
                secondCounter++;
        }
        if(firstCounter == 0)
            firstChild.push_back(firstGene);
        if(secondCounter == 0)
            secondChild.push_back(secondGene);
    }
    firstChild.insert( firstChild.begin() + start, second.genes.begin() + start, second.genes.begin() + end + 1);
    secondChild.insert( secondChild.begin() + start, first.genes.begin() + start, first.genes.begin() + end + 1);
    first.genes = firstChild;
    second.genes = secondChild;
}

void Genetic::mutate(double mutationRate, Chromosome& chromosome) const{
    uniform_int_distribution<int>  firstInt(1, chromosome.genes.size() - 2);
    uniform_real_distribution<double> distribution(0.0,1.0);
    double random = distribution(generator);
    if(random <= mutationRate){
        int start = firstInt(generator);
        uniform_int_distribution<int>  secondInt(start + 1, chromosome.genes.size() - 1);
        int end = secondInt(generator);
        swap(chromosome.genes[start], chromosome.genes[end]);
    }
}

void Genetic::initializePopulation(int populationSize, int chromosomeSize) {
    unsigned seed;
    vector<int> genes;
    for(int i=0; i<chromosomeSize; i++){
        genes.push_back(i);
    }
    for(int i=0; i<populationSize; i++){
        seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle(genes.begin()+1, genes.end(), default_random_engine(seed));
        Chromosome chromosome{genes, matrix};
        population.push_back(chromosome);
    }
    sort(population.begin(), population.end());
}

Chromosome Genetic::tournamentSelection(int tournamentSize) {
    uniform_real_distribution<double> randomInt(0,population.size() - 1);
    int random = randomInt(generator);
    int min = population[random].value();
    int minIndex = random;
    for (int j = 0; j < tournamentSize - 1; j++) {
        random = randomInt(generator);
        if (population[random].value() < min) {
            min = population[random].value();
            minIndex = random;
        }
    }
    return population[minIndex];
}

void Genetic::nextGenerationTournament(int eliteSize, int tournamentSize, double mutationRate) {
    vector<Chromosome> nextGeneration;
    for(int i=0; i<eliteSize; i += 2) {
        crossover(population[i], population[i + 1]);
        mutate(mutationRate, population[i]);
        mutate(mutationRate, population[i + 1]);
        population[i].calcValue(matrix);
        population[i + 1].calcValue(matrix);
        nextGeneration.push_back(population[i]);
        nextGeneration.push_back(population[i + 1]);
    }
    for(int i=0; i<(population.size() - eliteSize)/2; i++) {
        Chromosome first = tournamentSelection(tournamentSize);
        Chromosome second = tournamentSelection(tournamentSize);
        crossover(first, second);
        mutate(mutationRate, first);
        mutate(mutationRate, second);
        first.calcValue(matrix);
        second.calcValue(matrix);
        nextGeneration.push_back(first);
        nextGeneration.push_back(second);
    }
    population = nextGeneration;
}

void Genetic::rankSelection(int eliteSize) {
    uniform_real_distribution<double> distribution(0.0,1.0);
    int factor = 0;
    double range = 0;
    vector<double> ranges;
    vector<Chromosome> pool;
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

Chromosome Genetic::geneticAlgorithm(int populationSize, int chromosomeSize, int eliteSize, int tournamentSize, double mutationRate, int generations){
    initializePopulation(populationSize, chromosomeSize);
    for(int i=0; i<generations; i++){
        nextGenerationTournament(eliteSize, tournamentSize, mutationRate);
        sort(population.begin(), population.end());
    }
    return population[0];
}

void Genetic::printPopulation() const{
    for(Chromosome chromosome : population)
        chromosome.printChromosome();
}
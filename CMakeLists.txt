cmake_minimum_required(VERSION 3.15)
project(geneticAlgorithm)

set(CMAKE_CXX_STANDARD 17)

add_executable(geneticAlgorithm main.cpp Matrix.cpp Matrix.h GeneticAlgorithm.cpp GeneticAlgorithm.h Chromosome.cpp Chromosome.h)
#include "geneticalgorithm.h"

genalg::GeneticAlgorithm::GeneticAlgorithm(Problem* problem, size_t populationSize, double crossoverProbability, double mutationProbability) : problem(problem), populationSize(populationSize), crossoverProbability(crossoverProbability), mutationProbability(mutationProbability) {
	// TODO: randomize
}

void genalg::GeneticAlgorithm::run(size_t iterationCount) {
	
}
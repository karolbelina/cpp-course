#include "geneticalgorithm.h"

template<class Problem>
genalg::GeneticAlgorithm<Problem>::GeneticAlgorithm(Problem* problem, size_t populationSize, double crossoverProbability, double mutationProbability) : problem(problem), populationSize(populationSize), crossoverProbability(crossoverProbability), mutationProbability(mutationProbability) {
	// TODO: randomize
}

template<class Problem>
void genalg::GeneticAlgorithm<Problem>::run(size_t iterationCount) {
	
}
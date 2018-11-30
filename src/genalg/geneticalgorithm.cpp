#include "geneticalgorithm.h"

template<class Problem>
genalg::GeneticAlgorithm<Problem>::GeneticAlgorithm(Problem* problem, size_t populationSize, double crossoverProbability, double mutationProbability) : problem(problem), populationSize(populationSize), crossoverProbability(crossoverProbability), mutationProbability(mutationProbability) {
	for(size_t i = 0; i < populationSize; i++) {
		population.push_back(new Individual());
	}
}

template<class Problem>
void genalg::GeneticAlgorithm<Problem>::run(size_t iterationCount) {
	for(size_t i = 0; i < iterationCount; i++) {
		step();
	}
}

template<class Problem>
template<class Gene>
void genalg::GeneticAlgorithm<Problem>::step() {
	std::map<genalg::Individual<Gene>*, double> fitnessMap = evaluatePopulation();
}

template<class Problem>
template<class Gene>
std::map<genalg::Individual<Gene>*, double> genalg::GeneticAlgorithm<Problem>::evaluatePopulation() {
	std::map<genalg::Individual<Gene>*, double> map;

	for(genalg::Individual<Gene>* individual : population) {
		map.insert(std::pair<genalg::Individual<Gene>, double>(individual, problem->evaluate(individual)));
	}

	return map;
}
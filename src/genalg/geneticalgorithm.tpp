#include "geneticalgorithm.h"

template<class Problem>
inline genalg::GeneticAlgorithm<Problem>::GeneticAlgorithm(Problem* problem, size_t populationSize, double crossoverProbability, double mutationProbability) : problem(problem), populationSize(populationSize), crossoverProbability(crossoverProbability), mutationProbability(mutationProbability) {
	for(size_t i = 0; i < populationSize; i++) {
		population.push_back(Individual<typename Problem::Gene>{});
	}
}

template<class Problem>
inline void genalg::GeneticAlgorithm<Problem>::run(size_t iterationCount) {
	for(size_t i = 0; i < iterationCount; i++) {
		step();
	}
}

template<class Problem>
inline void genalg::GeneticAlgorithm<Problem>::step() {
	std::map<genalg::Individual<typename Problem::Gene>, double> fitnessMap = evaluatePopulation();

}

template<class Problem>
inline std::map<genalg::Individual<typename Problem::Gene>, double> genalg::GeneticAlgorithm<Problem>::evaluatePopulation() {
	std::map<genalg::Individual<typename Problem::Gene>, double> map;

	for(genalg::Individual<typename Problem::Gene> individual : population) {
		map.insert(std::pair<genalg::Individual<typename Problem::Gene>, double>(individual, problem->evaluate(individual)));
	}

	return map;
}
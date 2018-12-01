#include "geneticalgorithm.h"

#include <random>

template<class Problem>
inline genalg::GeneticAlgorithm<Problem>::GeneticAlgorithm(Problem* problem, size_t populationSize, double crossoverProbability, double mutationProbability) : problem(problem), populationSize(populationSize), crossoverProbability(crossoverProbability), mutationProbability(mutationProbability), population(populationSize) {}

template<class Problem>
inline void genalg::GeneticAlgorithm<Problem>::run(size_t iterationCount) {
	for(size_t i = 0; i < iterationCount; i++) {
		step();
	}
}

template<class Problem>
genalg::Individual<typename Problem::Gene> genalg::GeneticAlgorithm<Problem>::getFittestIndividual() {
    std::map<genalg::Individual<typename Problem::Gene>, double> fitnessMap = evaluatePopulation();

    return std::max_element(fitnessMap.begin(), fitnessMap.end(), [](const auto &left, const auto &right) {return left.second < right.second; })->first;
}

template<class Problem>
inline void genalg::GeneticAlgorithm<Problem>::step() {
	std::map<genalg::Individual<typename Problem::Gene>, double> fitnessMap = evaluatePopulation();

    std::vector<Individual<typename Problem::Gene>> nextGeneration;

    while(nextGeneration.size() < populationSize) {
        std::pair<genalg::Individual<typename Problem::Gene>, genalg::Individual<typename Problem::Gene>> children = genalg::Individual<typename Problem::Gene>::crossover({selectParent(fitnessMap), selectParent(fitnessMap)}, crossoverProbability);

        nextGeneration.push_back(children.first);

        if(nextGeneration.size() != populationSize) {
            nextGeneration.push_back(children.second);
        }
    }

    for(Individual<typename Problem::Gene> individual : nextGeneration) {
        individual.mutate(mutationProbability);
    }

    population = nextGeneration;
}

template<class Problem>
inline std::map<genalg::Individual<typename Problem::Gene>, double> genalg::GeneticAlgorithm<Problem>::evaluatePopulation() {
	std::map<genalg::Individual<typename Problem::Gene>, double> map;

	for(genalg::Individual<typename Problem::Gene> individual : population) {
		map.insert(std::pair<genalg::Individual<typename Problem::Gene>, double>(individual, problem->evaluate(individual)));
	}

	return map;
}

template<class Problem>
genalg::Individual<typename Problem::Gene> genalg::GeneticAlgorithm<Problem>::selectParent(std::map<Individual<typename Problem::Gene>, double> fitnessMap) {
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<> distribution(0, population.size());

    Individual<typename Problem::Gene> first = population.at(distribution(rng)), second = population.at(distribution(rng));

    return fitnessMap.at(first) > fitnessMap.at(second) ? first : second;
}
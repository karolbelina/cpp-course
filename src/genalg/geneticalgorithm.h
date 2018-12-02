#pragma once

#include "individual.h"

#include <unordered_map>
#include <vector>

namespace genalg {
	template<class Problem>
	class GeneticAlgorithm {
	public:
		GeneticAlgorithm() = default;
		GeneticAlgorithm(Problem* problem, size_t populationSize, double crossoverProbability, double mutationProbability);

		void run(size_t iterationCount);
		Individual<typename Problem::Gene> getFittestIndividual();

	private:
		void step();
		std::unordered_map<Individual<typename Problem::Gene>, double> evaluatePopulation();
		Individual<typename Problem::Gene> selectParent(std::unordered_map<Individual<typename Problem::Gene>, double> fitnessMap);

		Problem* problem;
		size_t populationSize;
		double crossoverProbability;
		double mutationProbability;
		std::vector<Individual<typename Problem::Gene>> population;
	};
}

#include "geneticalgorithm.tpp"
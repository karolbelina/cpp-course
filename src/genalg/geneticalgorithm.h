#pragma once

#include "individual.h"

#include <map>
#include <vector>

namespace genalg {
	template<class Problem>
	class GeneticAlgorithm {
	public:
		GeneticAlgorithm() = delete;
		GeneticAlgorithm(Problem* problem, size_t populationSize, double crossoverProbability, double mutationProbability);

		void run(size_t iterationCount);
        Individual<typename Problem::Gene> getFittestIndividual();

	private:
		void step();
		std::map<Individual<typename Problem::Gene>, double> evaluatePopulation();
        Individual<typename Problem::Gene> selectParent(std::map<Individual<typename Problem::Gene>, double> fitnessMap);

		Problem* problem;
		size_t populationSize;
		double crossoverProbability;
		double mutationProbability;
		std::vector<Individual<typename Problem::Gene>> population; // TODO: class Problem::Gene?
	};
}

#include "geneticalgorithm.tpp"
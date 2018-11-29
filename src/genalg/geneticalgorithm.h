#pragma once

#include "individual.h"

#include <vector>

namespace genalg {
	template<class Problem>
	class GeneticAlgorithm {
	public:
		GeneticAlgorithm(Problem* problem, size_t populationSize, double crossoverProbability, double mutationProbability);
		void run(size_t iterationCount);

	private:
		Problem* problem;
		size_t populationSize;
		double crossoverProbability;
		double mutationProbability;

		std::vector<Individual*> population;
	};
}
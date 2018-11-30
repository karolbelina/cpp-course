#pragma once

#include "individual.h"

#include <map>
#include <vector>

namespace genalg {
	template<class Problem>
	class GeneticAlgorithm {
	public:
		GeneticAlgorithm(Problem* problem, size_t populationSize, double crossoverProbability, double mutationProbability);

		void run(size_t iterationCount);

	private:
		void step();
		template<class Gene> std::map<Individual<Gene>*, double> evaluatePopulation();

		Problem* problem;
		size_t populationSize;
		double crossoverProbability;
		double mutationProbability;
		template<class Gene> std::vector<Individual<Gene>*> population;
	};
}
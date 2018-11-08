#pragma once

#include <vector>

namespace genalg {
	template<class T>
	class GeneticAlgorithm {
	public:
		GeneticAlgorithm(size_t populationSize, double crossoverProbability, double mutationProbability);
		void run(size_t iterationCount);

	private:
		size_t populationSize;
		double crossoverProbability;
		double mutationProbability;

		std::vector<Individual*> population;
	};
}
#pragma once

#include <unordered_map>
#include <vector>

namespace genalg {
	template<class Problem>
	class GeneticAlgorithm {
	public:
		struct Individual {
			Individual() = delete;
			Individual(size_t genotypeSize, GeneticAlgorithm* owner);
			Individual(std::vector<typename Problem::Gene> genotype, GeneticAlgorithm* owner);
			Individual(const Individual &other);
			Individual& operator=(const Individual &other);

			bool operator==(const Individual &other) const;

			Individual& operator++(int);
			Individual operator+(const Individual &other);

			std::vector<typename Problem::Gene> genotype;
			GeneticAlgorithm* owner;

			struct hash {
				size_t operator()(const Individual &individual) const;
			};
		};

		GeneticAlgorithm() = delete;
		GeneticAlgorithm(Problem* problem, size_t populationSize, double crossoverProbability, double mutationProbability);

		void run(double time);
		Individual getFittestIndividual();

	private:
		std::unordered_map<Individual, double, typename Individual::hash> assessPopulation();
		Individual selectParent(std::unordered_map<Individual, double, typename Individual::hash> fitnessMap);

		Problem* problem;
		size_t populationSize;
		double crossoverProbability;
		double mutationProbability;
		std::vector<Individual> population;
	};
}

#include "geneticalgorithm.tpp"
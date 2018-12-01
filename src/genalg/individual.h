#pragma once

#include <sstream>
#include <vector>

namespace genalg {
	template<class Gene>
	struct Individual {
		Individual() = default;
        Individual(size_t genotypeSize);
		Individual(std::vector<Gene> genotype);
		Individual(const Individual &other);

		void mutate(double probability);
		static std::pair<Individual, Individual> crossover(std::pair<Individual, Individual> parents, double probability);

		std::vector<Gene> genotype;
	};
}

#include "individual.tpp"
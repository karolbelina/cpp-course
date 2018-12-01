#pragma once

#include <sstream>
#include <vector>

namespace genalg {
	template<class Gene>
	struct Individual {
		Individual() = default;
		Individual(std::vector<Gene> genotype);
		Individual(const Individual &other);

		void mutate(double probability);
		std::vector<Individual> crossover(const Individual &other, double probability) const;

		std::vector<Gene> genotype;
	};
}

#include "individual.tpp"
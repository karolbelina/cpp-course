#pragma once

#include <sstream>
#include <vector>

namespace genalg {
	template<class Gene>
	struct Individual {
		Individual() = delete;
		Individual(std::vector<Gene*> genotype);
		Individual(const Individual &other);
		friend std::ostream& operator<<(std::ostream &stream, const Individual &individual);

		void mutate(double probability);
		std::vector<Individual*> crossover(Individual &other, double probability);

		std::vector<Gene*> genotype;
	};
}
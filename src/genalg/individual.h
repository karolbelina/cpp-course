#pragma once

#include <vector>

namespace genalg {
	template<class Gene>
	class Individual {
	public:
		Individual() = delete;
		Individual(std::vector<Gene*> genotype);
		Individual(const Individual &other);

		std::vector<bool> getGenotype() const;
		void mutate(double probability);
		std::vector<Individual*> crossover(Individual &other, double probability);

	protected:
		std::vector<Gene*> genotype;
	};
}
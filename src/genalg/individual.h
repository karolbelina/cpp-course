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
        Individual& operator=(const Individual &other);

        bool operator==(const Individual &other) const;

		void mutate(double probability);
		static std::pair<Individual, Individual> crossover(std::pair<Individual, Individual> parents, double probability);

		std::vector<Gene> genotype;
	};
}

namespace std {
    template<class Gene>
    struct hash<genalg::Individual<Gene>> {
        size_t operator()(const genalg::Individual<Gene> &individual) const {
            size_t seed = 0;

            for(Gene gene : individual.genotype) {
                seed ^= std::hash<Gene>()(gene);
            }

            return seed;
        }
    };
}

#include "individual.tpp"
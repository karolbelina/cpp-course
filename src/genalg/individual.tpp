#include "individual.h"

#include <random>

template<class Gene>
inline genalg::Individual<Gene>::Individual(std::vector<Gene> genotype) {
	this->genotype = std::vector<Gene>(genotype);
}

template<class Gene>
inline genalg::Individual<Gene>::Individual(const Individual<Gene> &other) : Individual<Gene>(other.genotype) {}

template<class Gene>
inline void genalg::Individual<Gene>::mutate(double probability) {
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<> distribution(0, 1);

	for(Gene gene : genotype) {
		if(distribution(rng) < probability) {
            gene.mutate();
		}
	}
}

template<class Gene>
inline std::pair<genalg::Individual<Gene>, genalg::Individual<Gene>> genalg::Individual<Gene>::crossover(std::pair<genalg::Individual<Gene>, genalg::Individual<Gene>> parents, double probability) {
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<> distribution(0, 1);

	if(distribution(rng) < probability) {
		std::uniform_int_distribution<> distribution(1, parents.first.genotype.size() - 1);

		genalg::Individual<Gene> first(parents.first.genotype);
		genalg::Individual<Gene> second(parents.second.genotype);

		std::swap_ranges(first.genotype.begin(), first.genotype.begin() + distribution(rng), second.genotype.begin());

		return std::pair<genalg::Individual<Gene>, genalg::Individual<Gene>>(first, second);
	}

	return parents;
}
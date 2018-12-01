#include "individual.h"

#include <random>

template<class Gene>
genalg::Individual<Gene>::Individual(std::vector<Gene> genotype) {
	this->genotype = std::vector<Gene>(genotype);
}

template<class Gene>
genalg::Individual<Gene>::Individual(const Individual<Gene> &other) : Individual<Gene>(other.genotype) {}

template<class Gene>
void genalg::Individual<Gene>::mutate(double probability) {
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<> distribution(0, 1);

	for(Gene gene : genotype) {
		if(distribution(rng) < probability) {
			gene->mutate();
		}
	}
}

template<class Gene>
std::vector<genalg::Individual<Gene>> genalg::Individual<Gene>::crossover(const genalg::Individual<Gene> &other, double probability) const {
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<> distribution(0, 1);

	if(distribution(rng) < probability) {
		std::uniform_int_distribution<> distrubution(1, genotype.size() - 1);

		genalg::Individual<Gene> first(genotype);
		genalg::Individual<Gene> second(other.genotype);

		std::swap_ranges(first.genotype.begin(), first.genotype.begin() + distribution(rng), second.genotype.begin());

		return std::vector<genalg::Individual<Gene>>({first, second});
	}

	return std::vector<genalg::Individual<Gene>>();
}
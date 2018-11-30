#include "individual.h"

#include <random>

template<class Gene>
genalg::Individual<Gene>::Individual(std::vector<Gene*> genotype) {
	for(Gene* gene : genotype) {
		this->genotype.push_back(gene->clone());
	}
}

template<class Gene>
genalg::Individual<Gene>::Individual(const Individual<Gene> &other) : Individual<Gene>(other.genotype) {}

// TODO: try to fix this ugly piece of shit
namespace genalg {
	template<class Gene>
	std::ostream& operator<<(std::ostream &stream, const Individual<Gene> &individual) {
		for(Gene* gene : individual.genotype) {
			stream << gene;
		}

		return stream;
	}
}

template<class Gene>
void genalg::Individual<Gene>::mutate(double probability) {
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<> distribution(0, 1);

	for(Problem::Individual::Gene* gene : genotype) {
		if(distribution(rng) < probability) {
			gene->mutate();
		}
	}
}

template<class Gene>
std::vector<genalg::Individual<Gene>*> genalg::Individual<Gene>::crossover(genalg::Individual<Gene> &other, double probability) {
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<> distribution(0, 1);

	if(distribution(rng) < probability) {
		std::uniform_int_distribution<> distrubution(1, genotype.size() - 1);

		// TODO: swap_ranges http://www.cplusplus.com/reference/algorithm/swap_ranges/

		// reserve i wtedy iteratorem wstawiamy copy_n
	}

	return std::vector<genalg::Problem::Individual*>();
}
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
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> distribution(0, 1);

	for(Problem::Individual::Gene* gene : genotype) {
		if(distribution(gen) < probability) {
			gene->mutate();
		}
	}
}

template<class Gene>
std::vector<genalg::Individual<Gene>*> genalg::Individual<Gene>::crossover(genalg::Individual<Gene> &other, double probability) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> distribution(0, 1);

	if(distribution(gen) < probability) {
		std::uniform_int_distribution<> distrubution(1, 6);
	}

	return std::vector<genalg::Problem::Individual*>();
}



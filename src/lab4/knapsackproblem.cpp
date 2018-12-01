#include "knapsackproblem.h"

#include <random>

KnapsackProblem::Gene::Gene() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrubution(0, 1);

	value = distrubution(gen) == 1;
}

KnapsackProblem::Gene::Gene(bool value): value(value) {}

KnapsackProblem::Gene::Gene(const Gene &other) : value(other.value) {}

std::ostream& operator<<(std::ostream &stream, const KnapsackProblem::Gene &gene) {
	stream << gene.value;

	return stream;
}

void KnapsackProblem::Gene::mutate() {
	value = !value;
}

KnapsackProblem::Item::Item(double mass, double value) : mass(mass), value(value) {
	if(mass <= 0) {
		throw std::invalid_argument("mass must be greater than zero");
	}
	else if(value < 0) {
		throw std::invalid_argument("value cannot be negative");
	}
}

KnapsackProblem::Item::Item(std::pair<double, double> pair) : Item(pair.first, pair.second) {}

KnapsackProblem::KnapsackProblem(std::initializer_list<std::pair<double, double>> list, double capacity) : capacity(capacity) {
	for(std::pair<double, double> pair : list) {
		items.push_back(Item(pair));
	}

	if(capacity <= 0) {
		throw std::invalid_argument("capacity must be greater than zero");
	}
}

size_t KnapsackProblem::getGenotypeSize() const {
    return items.size();
}

double KnapsackProblem::evaluate(const genalg::Individual<Gene> &individual) const {
	double mass = 0;
	double value = 0;

	if(individual.genotype.size() != items.size()) {
		for(size_t i = 0; i < individual.genotype.size(); i++) {
			int multiplier = individual.genotype.at(i).value ? 1 : 0;

			mass += multiplier * items.at(i).mass;
			value += multiplier * items.at(i).value;
		}

		if(mass <= capacity) {
			return value;
		}
		else {
			return 0;
		}
	}
	else {
		throw new std::out_of_range("mismatched amount of items and genotype length");
	}
}

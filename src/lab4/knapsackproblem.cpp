#include "knapsackproblem.h"

#include <random>

KnapsackProblem::Gene::Gene() {
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<> distribution(0, 1);

	value = distribution(rng) == 1;
}

KnapsackProblem::Gene::Gene(bool value): value(value) {}

KnapsackProblem::Gene::Gene(const Gene &other) : value(other.value) {}

KnapsackProblem::Gene& KnapsackProblem::Gene::operator=(const Gene &other) {
	if(this == &other) {
		return *this;
	}

	value = other.value;

	return *this;
}

std::ostream& operator<<(std::ostream &stream, const KnapsackProblem::Gene &gene) {
	stream << gene.value;

	return stream;
}

bool KnapsackProblem::Gene::operator==(const Gene &other) const {
	return value == other.value;
}

void KnapsackProblem::Gene::mutate() {
	value = !value;
}

KnapsackProblem::Item::Item(double value, double mass) : value(value), mass(mass) {
	if(mass <= 0) {
		throw std::invalid_argument("mass must be greater than zero");
	}
	else if(value < 0) {
		throw std::invalid_argument("value cannot be negative");
	}
}

KnapsackProblem::Item::Item(std::pair<double, double> pair) : Item(pair.first, pair.second) {}

KnapsackProblem::KnapsackProblem(std::initializer_list<std::pair<double, double>> list, double capacity) : capacity(capacity) {
	if(capacity <= 0) {
		throw std::invalid_argument("capacity must be greater than zero");
	}

	for(std::pair<double, double> pair : list) {
		items.push_back(Item(pair));
	}
}

size_t KnapsackProblem::getGenotypeSize() const {
	return items.size();
}

double KnapsackProblem::evaluate(const genalg::Individual<Gene> &individual) const {
	double value = 0;
	double mass = 0;

	if(individual.genotype.size() == items.size()) {
		for(size_t i = 0; i < individual.genotype.size(); i++) {
			int multiplier = individual.genotype.at(i).value ? 1 : 0;

			value += multiplier * items.at(i).value;
			mass += multiplier * items.at(i).mass;
		}

		return mass <= capacity ? value : 0;
	}
	else {
		throw new std::runtime_error("mismatched amount of items and genotype length");
	}
}

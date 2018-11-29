#include "knapsackproblem.h"

#include <random>

KnapsackProblem::Gene::Gene() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrubution(0, 1);

	value = distrubution(gen) == 1;
}

KnapsackProblem::Gene::Gene(bool value): value(value) {
}

KnapsackProblem::Gene::Gene(const Gene &other) : value(other.value) {
}

KnapsackProblem::Gene* KnapsackProblem::Gene::clone() {
	return new Gene(*this);
}

bool KnapsackProblem::Gene::evaluate() {
	return value;
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

double KnapsackProblem::evaluate(const genalg::Individual<Gene> &individual) {
	double mass = 0;
	double value = 0;

	for(size_t i = 0; i < individual.getGenotype().size(); i++) {
		int multiplier = individual.getGenotype().at(i) ? 1 : 0;

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
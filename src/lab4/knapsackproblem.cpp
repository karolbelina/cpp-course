#include "knapsackproblem.h"

KnapsackProblem::Individual::Gene::Gene(bool value) : value(value) {}

KnapsackProblem::Individual::Gene::Gene(const Gene &other) : value(other.value) {}

bool KnapsackProblem::Individual::Gene::evaluate() {
	return value;
}

void KnapsackProblem::Individual::Gene::mutate() {
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

KnapsackProblem::KnapsackProblem(std::initializer_list<std::pair<double, double>> list) {
	for(std::pair<double, double> pair : list) {
		items.push_back(Item(pair));
	}
}
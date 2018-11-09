#include "knapsackproblem.h"

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

double KnapsackProblem::evaluate(const genalg::Problem::Individual &individual) {
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
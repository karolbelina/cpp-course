#pragma once

#include "problem.h"

#include <vector>

class KnapsackProblem : public genalg::Problem {
public:
	struct Item {
		Item(double mass, double value);
		Item(std::pair<double, double> pair);

		double mass;
		double value;
	};

	KnapsackProblem(std::initializer_list<std::pair<double, double>> list, double capacity);

	double evaluate(const genalg::Problem::Individual &individual) override;

private:
	std::vector<Item> items;
	double capacity;
};
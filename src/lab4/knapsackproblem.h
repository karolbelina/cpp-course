#pragma once

#include "individual.h"

#include <vector>

class KnapsackProblem {
public:
	struct Item {
		Item(double mass, double value);
		Item(std::pair<double, double> pair);

		double mass;
		double value;
	};

	struct Gene {
		Gene();
		Gene(bool value);
		Gene(const Gene &other);
		Gene* clone();

		void mutate();

		bool value;
	};

	KnapsackProblem(std::initializer_list<std::pair<double, double>> list, double capacity);

	double evaluate(const genalg::Individual<Gene> &individual);

private:
	std::vector<Item> items;
	double capacity;
};
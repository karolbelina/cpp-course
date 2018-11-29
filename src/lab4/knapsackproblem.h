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

	class Gene {
	public:
		Gene();
		Gene(bool value);
		Gene(const Gene &other);
		Gene* clone();

		bool evaluate();
		void mutate();

	private:
		bool value;
	};

	KnapsackProblem(std::initializer_list<std::pair<double, double>> list, double capacity);

	double evaluate(const genalg::Individual<Gene> &individual);

private:
	std::vector<Item> items;
	double capacity;
};
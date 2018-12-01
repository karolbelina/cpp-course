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
		friend std::ostream& operator<<(std::ostream &stream, const Gene &gene);

		void mutate();

		bool value;
	};

	KnapsackProblem(std::initializer_list<std::pair<double, double>> list, double capacity);

    size_t getGenotypeSize() const;
	double evaluate(const genalg::Individual<Gene> &individual) const;

private:
	std::vector<Item> items;
	double capacity;
};
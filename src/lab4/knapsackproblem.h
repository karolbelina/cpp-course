#pragma once

#include "individual.h"

#include <vector>

class KnapsackProblem {
public:
	struct Item {
		Item(double value, double mass);
		Item(std::pair<double, double> pair);

		double value;
		double mass;
	};

	struct Gene {
		Gene();
		Gene(bool value);
		Gene(const Gene &other);
        Gene& operator=(const Gene &other);

		friend std::ostream& operator<<(std::ostream &stream, const Gene &gene);
        bool operator==(const Gene &other) const;

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

namespace std {
    template<>
    struct hash<KnapsackProblem::Gene> {
        size_t operator()(const KnapsackProblem::Gene &gene) const {
            return hash<bool>()(gene.value);
        }
    }; 
}
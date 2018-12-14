#pragma once

#include "geneticalgorithm.h"

#include <vector>

template<typename Variation>
class KnapsackProblemBase {
public:
	struct Item {
		Item(double value, double mass);
		Item(std::pair<double, double> pair);

		double value;
		double mass;
	};

	struct Gene;

	KnapsackProblemBase(std::initializer_list<std::pair<double, double>> list, double capacity);
	virtual ~KnapsackProblemBase() = default;

	size_t getGenotypeSize() const;

protected:
	std::vector<Item> items;
	double capacity;
};

template<typename Variation>
class KnapsackProblem : public KnapsackProblemBase<Variation> {
	using KnapsackProblemBase<Variation>::KnapsackProblemBase;
};

template<>
class KnapsackProblem<bool> : public KnapsackProblemBase<bool> {
public:
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

	using KnapsackProblemBase<bool>::KnapsackProblemBase;

	double evaluate(const typename genalg::GeneticAlgorithm<KnapsackProblem<bool>>::Individual &individual) const;
};

template<>
class KnapsackProblem<int> : public KnapsackProblemBase<int> {
public:
	struct Gene {
		Gene();
		Gene(size_t value);
		Gene(const Gene &other);
		Gene& operator=(const Gene &other);

		friend std::ostream& operator<<(std::ostream &stream, const Gene &gene);
		bool operator==(const Gene &other) const;

		void mutate();

		size_t value;
	};

	using KnapsackProblemBase<int>::KnapsackProblemBase;

	double evaluate(const typename genalg::GeneticAlgorithm<KnapsackProblem<int>>::Individual &individual) const;
};

namespace std {
	template<>
	struct hash<KnapsackProblem<bool>::Gene> {
		size_t operator()(const KnapsackProblem<bool>::Gene &gene) const {
			return hash<bool>()(gene.value);
		}
	};

	template<>
	struct hash<KnapsackProblem<int>::Gene> {
		size_t operator()(const KnapsackProblem<int>::Gene &gene) const {
			return hash<int>()(gene.value);
		}
	};
}

#include "knapsackproblem.tpp"
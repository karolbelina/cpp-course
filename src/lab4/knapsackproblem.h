#pragma once

#include "problem.h"

class KnapsackProblem : public genalg::Problem {
public:
	class Individual {
	public:
		class Gene {
		public:
			Gene() = delete;
			Gene(bool value);
			Gene(const Gene &other);

			bool evaluate();
			void mutate();

		private:
			bool value;
		};

		virtual double getFitness() = 0;
		virtual void mutate() = 0;
		virtual std::vector<Individual> crossover(Individual &other) = 0;

	private:
		std::vector<Gene> genotype;
	};

	struct Item {
		Item(double mass, double value);
		Item(std::pair<double, double> pair);

		double mass;
		double value;
	};

	KnapsackProblem(std::initializer_list<std::pair<double, double>> list);

	double evaluate(Individual individual) {

	}

private:
	std::vector<Item> items;
};
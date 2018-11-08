#pragma once

#include <vector>

namespace genalg {
	class Problem {
	public:
		class Individual {
		public:
			class Gene {
				virtual int evaluate() = 0;
				virtual void mutate() = 0;
			};

			virtual double getFitness() = 0;
			virtual void mutate() = 0;
			virtual std::vector<Individual> crossover(Individual &other) = 0;

		private:
			std::vector<Gene> genotype;
		};
	};
}
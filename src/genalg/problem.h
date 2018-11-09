#pragma once

#include <vector>

namespace genalg {
	class Problem {
	public:
		class Individual {
		public:
			class Gene {
			public:
				Gene() = delete;
				Gene(bool value);
				Gene(const Gene &other);
				Gene* clone();

				bool evaluate();
				void mutate();

			private:
				bool value;
			};

			Individual() = delete;
			Individual(std::vector<Gene*> genotype);
			Individual(const Individual &other);

			std::vector<bool> getGenotype() const;
			void mutate(double probability);
			std::vector<Individual*> crossover(Individual &other, double probability);

		protected:
			std::vector<Gene*> genotype;
		};

		virtual double evaluate(const Individual &individual) = 0;
	};
}
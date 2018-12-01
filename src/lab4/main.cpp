#include <iostream>

#include "geneticalgorithm.h"
#include "knapsackproblem.h"

int main() {
	KnapsackProblem* problem = new KnapsackProblem({{5.0, 4.0}, {1.0, 1.0}, {4.0, 3.0}, {5.0, 2.0}}, 5.0);

	genalg::GeneticAlgorithm<KnapsackProblem>::GeneticAlgorithm(problem, 40, 0.7, 0.1);
}
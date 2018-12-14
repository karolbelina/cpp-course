#include <iostream>

#include "geneticalgorithm.h"
#include "knapsackproblem.h"

int main() {
	KnapsackProblem<int> kp({{5.0, 4.0}, {1.0, 1.0}, {4.0, 3.0}, {3.0, 2.0}}, 50.0);
	genalg::GeneticAlgorithm<KnapsackProblem<int>> ag(&kp, 100, 0.5, 0.1);

	std::cout << "Running..." << std::endl;

	ag.run(100);

	std::cout << "Done" << std::endl;

	std::cout << "Fittest individual: ";

	for(KnapsackProblem<int>::Gene gene : ag.getFittestIndividual().genotype) {
		std::cout << gene << " ";
	}

	std::cout << std::endl;
}
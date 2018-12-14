#include <iostream>
#include <string>

#include "geneticalgorithm.h"
#include "knapsackproblem.h"

int main() {
	KnapsackProblem<int> kp({{5.0, 4.0}, {1.0, 1.0}, {4.0, 3.0}, {3.0, 2.0}}, 50.0);
	genalg::GeneticAlgorithm<KnapsackProblem<int>> ag(&kp, 100, 0.5, 0.1);

	std::cout << "Running..." << std::endl;

	ag.run(15);

	std::cout << "Done" << std::endl << "Fittest individual: [";
	std::string separator;

	for(KnapsackProblem<int>::Gene gene : ag.getFittestIndividual().genotype) {
		std::cout << separator << gene;
		separator = ", ";
	}

	std::cout << ']' << std::endl;
}
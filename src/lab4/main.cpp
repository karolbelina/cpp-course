#include <iostream>

#include "geneticalgorithm.h"
#include "knapsackproblem.h"

int main() {
	KnapsackProblem kp({{5.0, 4.0}, {1.0, 1.0}, {4.0, 3.0}, {5.0, 2.0}}, 5.0);
	genalg::GeneticAlgorithm<KnapsackProblem> ag(&kp, 100, 0.5, 0.1);
	ag.run(400);
	
	for(KnapsackProblem::Gene gene : ag.getFittestIndividual().genotype) {
		std::cout << gene;
	}
}
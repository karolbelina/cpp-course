#include <iostream>

#include "geneticalgorithm.h"
#include "knapsackproblem.h"

int main() {
	genalg::GeneticAlgorithm<KnapsackProblem> ag(&KnapsackProblem::KnapsackProblem({{5.0, 4.0}, {1.0, 1.0}, {4.0, 3.0}, {5.0, 2.0}}, 5.0), 40, 0.7, 0.1);
    ag.run(40);
    
    for(KnapsackProblem::Gene gene : ag.getFittestIndividual().genotype) {
        std::cout << gene;
    }
}
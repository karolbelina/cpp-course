#include <iostream>

#include "geneticalgorithm.h"
#include "knapsackproblem.h"

int main() {
	KnapsackProblem<int> kp({{5.0, 4.0}, {1.0, 1.0}, {4.0, 3.0}, {5.0, 2.0}}, 10.0);
	genalg::GeneticAlgorithm<KnapsackProblem<int>> ag(&kp, 100, 0.5, 0.1);
}
#include "problem.h"

#include <random>

genalg::Problem::Individual::Gene::Gene() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrubution(0, 1);

	value = distribution(gen) == 1;
}

genalg::Problem::Individual::Gene::Gene(bool value): value(value) {}

genalg::Problem::Individual::Gene::Gene(const Gene &other) : value(other.value) {}

genalg::Problem::Individual::Gene* genalg::Problem::Individual::Gene::clone() {
	return new Gene(*this);
}

bool genalg::Problem::Individual::Gene::evaluate() {
	return value;
}

void genalg::Problem::Individual::Gene::mutate() {
	value = !value;
}

genalg::Problem::Individual::Individual(std::vector<Gene*> genotype) {
	for(Gene* gene : genotype) {
		this->genotype.push_back(gene->clone());
	}
}

genalg::Problem::Individual::Individual(const Individual &other) : Individual(other.genotype) {}

std::vector<bool> genalg::Problem::Individual::getGenotype() const {
	std::vector<bool> vector;

	for(Gene* gene : genotype) {
		vector.push_back(gene->evaluate());
	}

	return vector;
}

void genalg::Problem::Individual::mutate(double probability) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> distribution(0, 1);

	for(Problem::Individual::Gene* gene : genotype) {
		if(distribution(gen) < probability) {
			gene->mutate();
		}
	}
}

std::vector<genalg::Problem::Individual*> genalg::Problem::Individual::crossover(genalg::Problem::Individual &other, double probability) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> distribution(0, 1);

	if(distribution(gen) < probability) {
		std::uniform_int_distribution<> distrubution(1, 6);
	}

	return std::vector<genalg::Problem::Individual*>();
}
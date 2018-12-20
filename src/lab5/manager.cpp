#include "manager.h"

#include <fstream>
#include <sstream>
#include <string>

template<typename Variation>
KnapsackProblemManager<Variation>::KnapsackProblemManager(std::vector<std::pair<double, double>> items, double capacity, size_t populationSize, double crossoverProbability, double mutationProbability) : items(items), capacity(capacity), populationSize(populationSize), crossoverProbability(crossoverProbability), mutationProbability(mutationProbability), knapsackProblem(items, capacity), geneticAlgorithm(&knapsackProblem, populationSize, crossoverProbability, mutationProbability) {}

template<typename Variation>
inline void KnapsackProblemManager<Variation>::loadItems(std::string filename) {
	std::ifstream file;
	file.open(filename);

	if(file.is_open()) {
		items.clear();

		std::string line;
		while(getline(file, line)) {
			std::istringstream stream(line);

			double value, mass;

			stream >> value >> mass;

			items.push_back(std::pair<double, double>(value, mass));
		}
	}

	file.close();
	update();
}

template<typename Variation>
void KnapsackProblemManager<Variation>::setCapacity(double capacity) {
	this->capacity = capacity;
	update();
}

template<typename Variation>
void KnapsackProblemManager<Variation>::setPopulationSize(size_t populationSize) {
	this->populationSize = populationSize;
	updateGeneticAlgorithm();
}

template<typename Variation>
void KnapsackProblemManager<Variation>::setCrossoverProbability(double crossoverProbability) {
	this->crossoverProbability = crossoverProbability;
	updateGeneticAlgorithm();
}

template<typename Variation>
void KnapsackProblemManager<Variation>::setMutationProbability(double mutationProbability) {
	this->mutationProbability = mutationProbability;
	updateGeneticAlgorithm();
}

template<typename Variation>
void KnapsackProblemManager<Variation>::runAlgorithm(double time) {
	geneticAlgorithm.run(time);
}

template<typename Variation>
void KnapsackProblemManager<Variation>::getFittestIndividual(std::ostream &stream) {
	stream << '[';

	std::string separator;

	for(typename KnapsackProblem<Variation>::Gene gene : geneticAlgorithm.getFittestIndividual().genotype) {
		stream << separator << gene;
		separator = ", ";
	}

	stream << ']';
}

template<typename Variation>
void KnapsackProblemManager<Variation>::update() {
	knapsackProblem = KnapsackProblem<Variation>(items, capacity);
	updateGeneticAlgorithm();
}

template<typename Variation>
void KnapsackProblemManager<Variation>::updateGeneticAlgorithm() {
	geneticAlgorithm = genalg::GeneticAlgorithm<KnapsackProblem<Variation>>(&knapsackProblem, populationSize, crossoverProbability, mutationProbability);
}

KnapsackProblemManagerMultiplexer::KnapsackProblemManagerMultiplexer(std::vector<std::pair<double, double>> items, double capacity, size_t populationSize, double crossoverProbability, double mutationProbability) : type(Type::Bool), boolManager(items, capacity, populationSize, crossoverProbability, mutationProbability), intManager(items, capacity, populationSize, crossoverProbability, mutationProbability), doubleManager(items, capacity, populationSize, crossoverProbability, mutationProbability) {}

void KnapsackProblemManagerMultiplexer::changeVariation(Type type) {
	this->type = type;
}

void KnapsackProblemManagerMultiplexer::loadItems(std::string filename) {
	boolManager.loadItems(filename);
	intManager.loadItems(filename);
	doubleManager.loadItems(filename);
}

void KnapsackProblemManagerMultiplexer::setCapacity(double capacity) {
	boolManager.setCapacity(capacity);
	intManager.setCapacity(capacity);
	doubleManager.setCapacity(capacity);
}

void KnapsackProblemManagerMultiplexer::setPopulationSize(size_t populationSize) {
	boolManager.setPopulationSize(populationSize);
	intManager.setPopulationSize(populationSize);
	doubleManager.setPopulationSize(populationSize);
}

void KnapsackProblemManagerMultiplexer::setCrossoverProbability(double crossoverProbability) {
	boolManager.setCrossoverProbability(crossoverProbability);
	intManager.setCrossoverProbability(crossoverProbability);
	doubleManager.setCrossoverProbability(crossoverProbability);
}

void KnapsackProblemManagerMultiplexer::setMutationProbability(double mutationProbability) {
	boolManager.setMutationProbability(mutationProbability);
	intManager.setMutationProbability(mutationProbability);
	doubleManager.setMutationProbability(mutationProbability);
}

void KnapsackProblemManagerMultiplexer::runAlgorithm(double time) {
	if(type == Type::Bool) {
		boolManager.runAlgorithm(time);
	}
	else if(type == Type::Int) {
		intManager.runAlgorithm(time);
	}
	else if(type == Type::Double) {
		doubleManager.runAlgorithm(time);
	}
}

void KnapsackProblemManagerMultiplexer::getFittestIndividual(std::ostream &stream) {
	if(type == Type::Bool) {
		boolManager.getFittestIndividual(stream);
	}
	else if(type == Type::Int) {
		intManager.getFittestIndividual(stream);
	}
	else if(type == Type::Double) {
		doubleManager.getFittestIndividual(stream);
	}
}

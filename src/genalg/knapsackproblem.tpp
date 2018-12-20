#include "knapsackproblem.h"

#include <random>

template<typename Variation>
inline KnapsackProblemBase<Variation>::KnapsackProblemBase(std::vector<std::pair<double, double>> items, double capacity) : items(items), capacity(capacity) {}

template<typename Variation>
inline size_t KnapsackProblemBase<Variation>::getGenotypeSize() const {
	return items.size();
}

inline KnapsackProblem<bool>::Gene::Gene() {
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<> distribution(0, 1);

	value = distribution(rng) == 1;
}

inline KnapsackProblem<bool>::Gene::Gene(const Gene &other) : value(other.value) {}

inline KnapsackProblem<bool>::Gene& KnapsackProblem<bool>::Gene::operator=(const KnapsackProblem::Gene &other) {
	if(this == &other) {
		return *this;
	}

	value = other.value;

	return *this;
}

inline std::ostream& operator<<(std::ostream &stream, const KnapsackProblem<bool>::Gene &gene) {
	stream << gene.value;

	return stream;
}

inline bool KnapsackProblem<bool>::Gene::operator==(const Gene &other) const {
	return value == other.value;
}

inline void KnapsackProblem<bool>::Gene::mutate() {
	value = !value;
}

inline size_t KnapsackProblem<bool>::Gene::hash::operator()(const Gene &gene) const {
	return std::hash<bool>()(gene.value);
}

inline double KnapsackProblem<bool>::evaluate(const typename genalg::GeneticAlgorithm<KnapsackProblem<bool>>::Individual &individual) const {
	double value = 0;
	double mass = 0;

	if(individual.genotype.size() == items.size()) {
		for(size_t i = 0; i < individual.genotype.size(); i++) {
			int multiplier = individual.genotype.at(i).value ? 1 : 0;

			value += multiplier * items.at(i).first;
			mass += multiplier * items.at(i).second;
		}

		return mass <= capacity ? value : 0;
	}
	else {
		throw new std::runtime_error("mismatched amount of items and genotype length");
	}
}

inline KnapsackProblem<int>::Gene::Gene() {
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<> distribution(0, 3);

	value = distribution(rng);
}

inline KnapsackProblem<int>::Gene::Gene(const Gene &other) : value(other.value) {}

inline KnapsackProblem<int>::Gene& KnapsackProblem<int>::Gene::operator=(const KnapsackProblem::Gene &other) {
	if(this == &other) {
		return *this;
	}

	value = other.value;

	return *this;
}

inline std::ostream& operator<<(std::ostream &stream, const KnapsackProblem<int>::Gene &gene) {
	stream << gene.value;

	return stream;
}

inline bool KnapsackProblem<int>::Gene::operator==(const Gene &other) const {
	return value == other.value;
}

inline void KnapsackProblem<int>::Gene::mutate() {
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<> distribution(0, 1);

	int delta = distribution(rng) == 1 ? 1 : -1;
	value = std::max<size_t>(0, static_cast<int>(value) + delta);
}

inline size_t KnapsackProblem<int>::Gene::hash::operator()(const Gene &gene) const {
	return std::hash<int>()(gene.value);
}

inline double KnapsackProblem<int>::evaluate(const typename genalg::GeneticAlgorithm<KnapsackProblem<int>>::Individual &individual) const {
	double value = 0;
	double mass = 0;

	if(individual.genotype.size() == items.size()) {
		for(size_t i = 0; i < individual.genotype.size(); i++) {
			size_t multiplier = individual.genotype.at(i).value;

			value += multiplier * items.at(i).first;
			mass += multiplier * items.at(i).second;
		}

		return mass <= capacity ? value : 0;
	}
	else {
		throw new std::runtime_error("mismatched amount of items and genotype length");
	}
}

inline KnapsackProblem<double>::Gene::Gene() {
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<> distribution(0, 3);

	value = distribution(rng);
}

inline KnapsackProblem<double>::Gene::Gene(const Gene &other) : value(other.value) {
}

inline KnapsackProblem<double>::Gene& KnapsackProblem<double>::Gene::operator=(const KnapsackProblem::Gene &other) {
	if(this == &other) {
		return *this;
	}

	value = other.value;

	return *this;
}

inline std::ostream& operator<<(std::ostream &stream, const KnapsackProblem<double>::Gene &gene) {
	stream << gene.value;

	return stream;
}

inline bool KnapsackProblem<double>::Gene::operator==(const Gene &other) const {
	return value == other.value;
}

inline void KnapsackProblem<double>::Gene::mutate() {
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<> distribution(-1, 1);

	double delta = distribution(rng);
	value = std::max<double>(0, value + delta);
}

inline size_t KnapsackProblem<double>::Gene::hash::operator()(const Gene &gene) const {
	return std::hash<double>()(gene.value);
}

inline double KnapsackProblem<double>::evaluate(const typename genalg::GeneticAlgorithm<KnapsackProblem<double>>::Individual &individual) const {
	double value = 0;
	double mass = 0;

	if(individual.genotype.size() == items.size()) {
		for(size_t i = 0; i < individual.genotype.size(); i++) {
			double multiplier = individual.genotype.at(i).value;

			value += multiplier * items.at(i).first;
			mass += multiplier * items.at(i).second;
		}

		return mass <= capacity ? value : 0;
	}
	else {
		throw new std::runtime_error("mismatched amount of items and genotype length");
	}
}
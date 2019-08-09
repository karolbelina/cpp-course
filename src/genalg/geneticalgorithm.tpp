#include "geneticalgorithm.h"

#include <chrono>
#include <ctime>
#include <random>

template<class Problem>
inline genalg::GeneticAlgorithm<Problem>::Individual::Individual(size_t genotypeSize, GeneticAlgorithm* owner) : genotype(genotypeSize), owner(owner)
{
}

template<class Problem>
inline genalg::GeneticAlgorithm<Problem>::Individual::Individual(const Individual &other) : genotype(other.genotype), owner(other.owner)
{
}

template<class Problem>
inline typename genalg::GeneticAlgorithm<Problem>::Individual& genalg::GeneticAlgorithm<Problem>::Individual::operator=(const Individual &other)
{
  if (this == &other)
  {
    return *this;
  }

  genotype = other.genotype;
  owner = other.owner;

  return *this;
}

template<class Problem>
inline bool genalg::GeneticAlgorithm<Problem>::Individual::operator==(const Individual &other) const
{
  return genotype == other.genotype && owner == other.owner;
}

template<class Problem>
inline typename genalg::GeneticAlgorithm<Problem>::Individual& genalg::GeneticAlgorithm<Problem>::Individual::operator++(int)
{
  std::mt19937 rng(std::random_device{}());
  std::uniform_real_distribution<> distribution(0, 1);

  for (typename Problem::Gene &gene : genotype)
  {
    if (distribution(rng) < owner->mutationProbability)
    {
      gene.mutate();
    }
  }

  return *this;
}

template<class Problem>
inline typename genalg::GeneticAlgorithm<Problem>::Individual genalg::GeneticAlgorithm<Problem>::Individual::operator+(const Individual &other)
{
  std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<> distribution(1, other.genotype.size() - 1);

  typename genalg::GeneticAlgorithm<Problem>::Individual child(*this);

  std::copy_n(other.genotype.begin(), distribution(rng), child.genotype.begin());

  return child;
}

template<class Problem>
inline size_t genalg::GeneticAlgorithm<Problem>::Individual::hash::operator()(const Individual &individual) const
{
  size_t seed = individual.genotype.size();

  for (typename Problem::Gene gene : individual.genotype)
  {
    seed ^= typename Problem::Gene::hash()(gene) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
  }

  return seed;
}

template<class Problem>
inline genalg::GeneticAlgorithm<Problem>::GeneticAlgorithm(Problem* problem, size_t populationSize, double crossoverProbability, double mutationProbability, size_t saveBest) : problem(problem), populationSize(populationSize), crossoverProbability(crossoverProbability), mutationProbability(mutationProbability), saveBest(saveBest)
{
  for (size_t i = 0; i < populationSize; i++)
  {
    population.push_back(Individual(problem->getGenotypeSize(), this));
  }
}

template<class Problem>
inline void genalg::GeneticAlgorithm<Problem>::run(double time)
{
  std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();

  bool error;
  while (std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - startTime).count() < time)
  {
    std::unordered_map<Individual, double, typename Individual::hash> fitnessMap = assessPopulation(error);

    std::vector<Individual> nextGeneration;
    std::vector<Individual> fittestIndividuals = getFittestIndividuals(fitnessMap, saveBest);
    nextGeneration.insert(nextGeneration.end(), fittestIndividuals.begin(), fittestIndividuals.end());

    while (nextGeneration.size() < populationSize)
    {
      std::mt19937 rng(std::random_device{}());
      std::uniform_real_distribution<> distribution(0, 1);

      Individual firstParent = selectParent(fitnessMap);
      nextGeneration.push_back((distribution(rng) < crossoverProbability ? firstParent + selectParent(fitnessMap) : firstParent)++);
    }

    population = nextGeneration;
  }
}

template<class Problem>
inline typename genalg::GeneticAlgorithm<Problem>::Individual genalg::GeneticAlgorithm<Problem>::getFittestIndividual()
{
  bool error;
  std::unordered_map<Individual, double, typename Individual::hash> fitnessMap = assessPopulation(error);

  return std::max_element(fitnessMap.begin(), fitnessMap.end(), [](const std::pair<Individual, double> &left, const std::pair<Individual, double> &right)
  {
    return left.second < right.second;
  })->first;
}

template<class Problem>
inline std::unordered_map<typename genalg::GeneticAlgorithm<Problem>::Individual, double, typename genalg::GeneticAlgorithm<Problem>::Individual::hash> genalg::GeneticAlgorithm<Problem>::assessPopulation(bool &error)
{
  std::unordered_map<Individual, double, Individual::hash> map;

  for (const Individual &individual : population)
  {
    map.insert(std::pair<Individual, double>(individual, problem->evaluate(individual, error)));
  }

  return map;
}

template<class Problem>
inline typename genalg::GeneticAlgorithm<Problem>::Individual genalg::GeneticAlgorithm<Problem>::selectParent(std::unordered_map<Individual, double, typename Individual::hash> fitnessMap)
{
  std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<> distribution(0, population.size() - 1);

  Individual first = population.at(distribution(rng)), second = population.at(distribution(rng));

  return fitnessMap.at(first) > fitnessMap.at(second) ? first : second;
}

template<class Problem>
std::vector<typename genalg::GeneticAlgorithm<Problem>::Individual> genalg::GeneticAlgorithm<Problem>::getFittestIndividuals(std::unordered_map<Individual, double, typename Individual::hash> fitnessMap, size_t amount)
{
  std::vector<Individual> remainingIndividuals(population);
  std::vector<Individual> fittestIndividuals;

  for (size_t i = 0; i < amount; i++)
  {
    auto fittestIndividual = std::max_element(remainingIndividuals.begin(), remainingIndividuals.end(), [=](const Individual &left, const Individual &right)
    {
      return fitnessMap.at(left) < fitnessMap.at(right);
    });

    fittestIndividuals.push_back(*fittestIndividual);
    remainingIndividuals.erase(fittestIndividual);
  }

  return fittestIndividuals;
}
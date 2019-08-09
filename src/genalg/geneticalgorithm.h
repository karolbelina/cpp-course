#pragma once

#include <unordered_map>
#include <vector>

namespace genalg
{
  template<class Problem>
  class GeneticAlgorithm
  {
  public:
    struct Individual
    {
      Individual() = delete;
      Individual(size_t genotypeSize, GeneticAlgorithm* owner);
      Individual(const Individual &other);
      Individual& operator=(const Individual &other);

      bool operator==(const Individual &other) const;

      Individual& operator++(int);
      Individual operator+(const Individual &other);

      std::vector<typename Problem::Gene> genotype;
      GeneticAlgorithm* owner;

      struct hash
      {
        size_t operator()(const Individual &individual) const;
      };
    };

    GeneticAlgorithm() = delete;
    GeneticAlgorithm(Problem* problem, size_t populationSize, double crossoverProbability, double mutationProbability, size_t saveBest);

    void run(double time);
    Individual getFittestIndividual();

  private:
    std::unordered_map<Individual, double, typename Individual::hash> assessPopulation(bool &error);
    Individual selectParent(std::unordered_map<Individual, double, typename Individual::hash> fitnessMap);
    std::vector<Individual> getFittestIndividuals(std::unordered_map<Individual, double, typename Individual::hash> fitnessMap, size_t amount);

    Problem* problem;
    size_t populationSize;
    double crossoverProbability;
    double mutationProbability;
    size_t saveBest;
    std::vector<Individual> population;
  };
}

#include "geneticalgorithm.tpp"
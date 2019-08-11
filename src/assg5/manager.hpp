#pragma once

#include "geneticalgorithm.hpp"
#include "knapsackproblem.hpp"

#include <vector>

template<typename Variation>
class KnapsackProblemManager
{
public:
  KnapsackProblemManager() = delete;
  KnapsackProblemManager(std::vector<std::pair<double, double>> items, double capacity, size_t populationSize, double crossoverProbability, double mutationProbability, size_t saveBest);

  void loadItems(std::string filename);
  void setCapacity(double capacity);
  void setPopulationSize(size_t populationSize);
  void setCrossoverProbability(double crossoverProbability);
  void setMutationProbability(double mutationProbability);
  void runAlgorithm(double time);
  void getFittestIndividual(std::ostream &stream);

private:
  void update();
  void updateGeneticAlgorithm();

  std::vector<std::pair<double, double>> items;
  double capacity;
  size_t populationSize;
  double crossoverProbability;
  double mutationProbability;
  size_t saveBest;
  KnapsackProblem<Variation> knapsackProblem;
  genalg::GeneticAlgorithm<KnapsackProblem<Variation>> geneticAlgorithm;
};

class KnapsackProblemManagerMultiplexer
{
public:
  enum Type
  {
    Bool, Int, Double
  };

  KnapsackProblemManagerMultiplexer() = delete;
  KnapsackProblemManagerMultiplexer(std::vector<std::pair<double, double>> items, double capacity, size_t populationSize, double crossoverProbability, double mutationProbability, size_t saveBest);

  void changeVariation(Type type);
  void loadItems(std::string filename);
  void setCapacity(double capacity);
  void setPopulationSize(size_t populationSize);
  void setCrossoverProbability(double crossoverProbability);
  void setMutationProbability(double mutationProbability);
  void runAlgorithm(double time);
  void getFittestIndividual(std::ostream &stream);

private:
  Type type;
  KnapsackProblemManager<bool> boolManager;
  KnapsackProblemManager<int> intManager;
  KnapsackProblemManager<double> doubleManager;
};
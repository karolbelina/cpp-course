#include "customcommands.hpp"
#include "geneticalgorithm.hpp"
#include "knapsackproblem.hpp"
#include "manager.hpp"
#include "menuitem.hpp"

#include <iostream>
#include <string>

int main()
{
  KnapsackProblemManagerMultiplexer manager(std::vector<std::pair<double, double>>{
    {
      5.0, 4.0
    }, {1.0, 1.0}, {4.0, 3.0}, {3.0, 2.0}}, 5.0, 100, 0.5, 0.1, 10);

  const std::string source = "('Main menu','main';('Knapsack problem settings','kp';['Change variation','var','','ChangeVariationCommand'],['Load items','items','','LoadItemsCommand'],['Set capacity','cap','','SetCapacityCommand']),('Genetic algorithm settings','ga';['Set population size','popsize','','SetPopulationSizCommand'],['Set crossover probability','crossprob','','SetCrossoverProbability'],['Set mutation probability','mutprob','','SetMutationProbability']),['Run algorithm','run','','RunAlgorithmCommand'],['Get fittest individual','fittest','','GetFittestIndividualCommand'])";
  const menu::Environment environment = {
    {"ChangeVariationCommand", new ChangeVariationCommand(&manager)},
    {"LoadItemsCommand", new LoadItemsCommand(&manager)},
    {"SetCapacityCommand", new SetCapacityCommand(&manager)},
    {"SetPopulationSizeCommand", new SetPopulationSizeCommand(&manager)},
    {"SetMutationProbability", new SetMutationProbability(&manager)},
    {"SetCrossoverProbability", new SetCrossoverProbability(&manager)},
    {"RunAlgorithmCommand", new RunAlgorithmCommand(&manager)},
    {"GetFittestIndividualCommand", new GetFittestIndividualCommand(&manager)}
  };

  try
  {
    menu::MenuItem::importItem(source, environment)->run();
  }
  catch (const menu::parse_error &e)
  {
    std::cerr << e.what() << std::endl;
  }
}
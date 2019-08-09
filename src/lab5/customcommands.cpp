#include "constants.hpp"
#include "customcommands.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

static void getStringFromUserInput(std::string &destination)
{
  std::cout << PROMPT << SPACE;

  std::getline(std::cin, destination);
}

static bool getIntFromUserInput(int &destination)
{
  std::cout << PROMPT << SPACE;

  std::string input;
  std::getline(std::cin, input);
  std::istringstream stream(input);

  return static_cast<bool>(stream >> destination);
}

static bool getDoubleFromUserInput(double &destination)
{
  std::cout << PROMPT << SPACE;

  std::string input;
  std::getline(std::cin, input);
  std::istringstream stream(input);

  return static_cast<bool>(stream >> destination);
}

static bool getUnsignedIntFromUserInput(size_t &destination)
{
  std::cout << PROMPT << SPACE;

  std::string input;
  int temporary;
  std::getline(std::cin, input);
  std::istringstream stream(input);

  if (stream >> temporary)
  {
    if (temporary >= 0)
    {
      destination = temporary;
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}

ChangeVariationCommand::ChangeVariationCommand(KnapsackProblemManagerMultiplexer* manager) : Command(), manager(manager)
{
}

menu::Command* ChangeVariationCommand::clone() const
{
  return new ChangeVariationCommand(*this);
}

void ChangeVariationCommand::runCommand() const
{
  std::cout << "enter the variation (bool, int, double)" << COLON << std::endl;

  std::string type;
  getStringFromUserInput(type);

  if (type == "bool")
  {
    manager->changeVariation(KnapsackProblemManagerMultiplexer::Type::Bool);
    std::cout << "variation changed successfully to bool" << std::endl;
  }
  else if (type == "int")
  {
    manager->changeVariation(KnapsackProblemManagerMultiplexer::Type::Int);
    std::cout << "variation changed successfully to int" << std::endl;
  }
  else if (type == "double")
  {
    manager->changeVariation(KnapsackProblemManagerMultiplexer::Type::Double);
    std::cout << "variation changed successfully to double" << std::endl;
  }
  else
  {
    std::cout << "invalid variation" << std::endl;
  }
}

LoadItemsCommand::LoadItemsCommand(KnapsackProblemManagerMultiplexer* manager) : Command(), manager(manager)
{
}

menu::Command* LoadItemsCommand::clone() const
{
  return new LoadItemsCommand(*this);
}

void LoadItemsCommand::runCommand() const
{
  std::cout << "enter the filename" << COLON << std::endl;

  std::string filename;
  getStringFromUserInput(filename);

  try
  {
    manager->loadItems(filename);
    std::cout << "items have been successfully loaded" << std::endl;
  }
  catch (const std::ifstream::failure&)
  {
    std::cout << "file read error";
  }
}

SetCapacityCommand::SetCapacityCommand(KnapsackProblemManagerMultiplexer* manager) : Command(), manager(manager)
{
}

menu::Command* SetCapacityCommand::clone() const
{
  return new SetCapacityCommand(*this);
}

void SetCapacityCommand::runCommand() const
{
  std::cout << "enter the capacity" << COLON << std::endl;

  double capacity;

  if (getDoubleFromUserInput(capacity))
  {
    manager->setCapacity(capacity);
  }
  else
  {
    std::cout << "invalid capacity" << std::endl;
  }
}

SetPopulationSizeCommand::SetPopulationSizeCommand(KnapsackProblemManagerMultiplexer* manager) : Command(), manager(manager)
{
}

menu::Command* SetPopulationSizeCommand::clone() const
{
  return new SetPopulationSizeCommand(*this);
}

void SetPopulationSizeCommand::runCommand() const
{
  std::cout << "enter the capacity" << COLON << std::endl;

  size_t populationSize;

  if (getUnsignedIntFromUserInput(populationSize))
  {
    manager->setPopulationSize(populationSize);
  }
  else
  {
    std::cout << "invalid population size" << std::endl;
  }
}

SetMutationProbability::SetMutationProbability(KnapsackProblemManagerMultiplexer* manager) : Command(), manager(manager)
{
}

menu::Command* SetMutationProbability::clone() const
{
  return new SetMutationProbability(*this);
}

void SetMutationProbability::runCommand() const
{
  std::cout << "enter the mutation probability" << COLON << std::endl;

  double mutationProbability;

  if (getDoubleFromUserInput(mutationProbability))
  {
    if (mutationProbability >= 0 && mutationProbability <= 1)
    {
      manager->setMutationProbability(mutationProbability);
    }
    else
    {
      std::cout << "mutation probability must be a number between 0 and 1 inclusive" << std::endl;
    }
  }
  else
  {
    std::cout << "invalid mutation probability" << std::endl;
  }
}

SetCrossoverProbability::SetCrossoverProbability(KnapsackProblemManagerMultiplexer* manager) : Command(), manager(manager)
{
}

menu::Command* SetCrossoverProbability::clone() const
{
  return new SetCrossoverProbability(*this);
}

void SetCrossoverProbability::runCommand() const
{
  std::cout << "enter the crossover probability" << COLON << std::endl;

  double crossoverProbability;

  if (getDoubleFromUserInput(crossoverProbability))
  {
    if (crossoverProbability >= 0 && crossoverProbability <= 1)
    {
      manager->setCrossoverProbability(crossoverProbability);
    }
    else
    {
      std::cout << "crossover probability must be a number between 0 and 1 inclusive" << std::endl;
    }
  }
  else
  {
    std::cout << "invalid crossover probability" << std::endl;
  }
}

RunAlgorithmCommand::RunAlgorithmCommand(KnapsackProblemManagerMultiplexer* manager) : Command(), manager(manager)
{
}

menu::Command* RunAlgorithmCommand::clone() const
{
  return new RunAlgorithmCommand(*this);
}

void RunAlgorithmCommand::runCommand() const
{
  std::cout << "enter the duration in seconds" << COLON << std::endl;

  double time;

  if (getDoubleFromUserInput(time))
  {
    if (time >= 0)
    {
      std::cout << "running..." << std::endl;
      manager->runAlgorithm(time);
      std::cout << "done" << std::endl;
    }
    else
    {
      std::cout << "duration must not be negative" << std::endl;
    }
  }
  else
  {
    std::cout << "invalid duration" << std::endl;
  }
}

GetFittestIndividualCommand::GetFittestIndividualCommand(KnapsackProblemManagerMultiplexer* manager) : Command(), manager(manager)
{
}

menu::Command* GetFittestIndividualCommand::clone() const
{
  return new GetFittestIndividualCommand(*this);
}

void GetFittestIndividualCommand::runCommand() const
{
  std::cout << "fittest individual" << COLON << SPACE;
  manager->getFittestIndividual(std::cout);
}
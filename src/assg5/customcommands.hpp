#pragma once

#include "command.hpp"
#include "manager.hpp"

class ChangeVariationCommand : public menu::Command
{
public:
  ChangeVariationCommand(KnapsackProblemManagerMultiplexer* manager);
  virtual Command* clone() const override;
  void runCommand() const override final;

protected:
  KnapsackProblemManagerMultiplexer* manager;
};

class LoadItemsCommand : public menu::Command
{
public:
  LoadItemsCommand(KnapsackProblemManagerMultiplexer* manager);
  virtual Command* clone() const override;
  void runCommand() const override final;

protected:
  KnapsackProblemManagerMultiplexer* manager;
};

class SetCapacityCommand : public menu::Command
{
public:
  SetCapacityCommand(KnapsackProblemManagerMultiplexer* manager);
  virtual Command* clone() const override;
  void runCommand() const override final;

protected:
  KnapsackProblemManagerMultiplexer* manager;
};

class SetPopulationSizeCommand : public menu::Command
{
public:
  SetPopulationSizeCommand(KnapsackProblemManagerMultiplexer* manager);
  virtual Command* clone() const override;
  void runCommand() const override final;

protected:
  KnapsackProblemManagerMultiplexer* manager;
};

class SetMutationProbability : public menu::Command
{
public:
  SetMutationProbability(KnapsackProblemManagerMultiplexer* manager);
  virtual Command* clone() const override;
  void runCommand() const override final;

protected:
  KnapsackProblemManagerMultiplexer* manager;
};

class SetCrossoverProbability : public menu::Command
{
public:
  SetCrossoverProbability(KnapsackProblemManagerMultiplexer* manager);
  virtual Command* clone() const override;
  void runCommand() const override final;

protected:
  KnapsackProblemManagerMultiplexer* manager;
};

class RunAlgorithmCommand : public menu::Command
{
public:
  RunAlgorithmCommand(KnapsackProblemManagerMultiplexer* manager);
  virtual Command* clone() const override;
  void runCommand() const override final;

protected:
  KnapsackProblemManagerMultiplexer* manager;
};

class GetFittestIndividualCommand : public menu::Command
{
public:
  GetFittestIndividualCommand(KnapsackProblemManagerMultiplexer* manager);
  virtual Command* clone() const override;
  void runCommand() const override final;

protected:
  KnapsackProblemManagerMultiplexer* manager;
};
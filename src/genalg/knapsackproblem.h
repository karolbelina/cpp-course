#pragma once

#include "geneticalgorithm.h"

#include <vector>

template<typename Variation>
class KnapsackProblemBase
{
public:
  KnapsackProblemBase(std::vector<std::pair<double, double>> list, double capacity);
  virtual ~KnapsackProblemBase() = default;

  size_t getGenotypeSize() const;

protected:
  std::vector<std::pair<double, double>> items;
  double capacity;
};

template<typename Variation>
class KnapsackProblem : public KnapsackProblemBase<Variation>
{
  using KnapsackProblemBase<Variation>::KnapsackProblemBase;
};

template<>
class KnapsackProblem<bool> : public KnapsackProblemBase<bool>
{
public:
  struct Gene
  {
    Gene();
    Gene(const Gene &other);
    Gene& operator=(const Gene &other);

    friend std::ostream& operator<<(std::ostream &stream, const Gene &gene);
    bool operator==(const Gene &other) const;

    void mutate();

    bool value;

    struct hash
    {
      size_t operator()(const Gene &gene) const;
    };
  };

  using KnapsackProblemBase<bool>::KnapsackProblemBase;

  double evaluate(const typename genalg::GeneticAlgorithm<KnapsackProblem<bool>>::Individual &individual, bool &error) const;
};

template<>
class KnapsackProblem<int> : public KnapsackProblemBase<int>
{
public:
  struct Gene
  {
    Gene();
    Gene(const Gene &other);
    Gene& operator=(const Gene &other);

    friend std::ostream& operator<<(std::ostream &stream, const Gene &gene);
    bool operator==(const Gene &other) const;

    void mutate();

    size_t value;

    struct hash
    {
      size_t operator()(const Gene &gene) const;
    };
  };

  using KnapsackProblemBase<int>::KnapsackProblemBase;

  double evaluate(const typename genalg::GeneticAlgorithm<KnapsackProblem<int>>::Individual &individual, bool &error) const;
};

template<>
class KnapsackProblem<double> : public KnapsackProblemBase<double>
{
public:
  struct Gene
  {
    Gene();
    Gene(const Gene &other);
    Gene& operator=(const Gene &other);

    friend std::ostream& operator<<(std::ostream &stream, const Gene &gene);
    bool operator==(const Gene &other) const;

    void mutate();

    double value;

    struct hash
    {
      size_t operator()(const Gene &gene) const;
    };
  };

  using KnapsackProblemBase<double>::KnapsackProblemBase;

  double evaluate(const typename genalg::GeneticAlgorithm<KnapsackProblem<double>>::Individual &individual, bool &error) const;
};

#include "knapsackproblem.tpp"
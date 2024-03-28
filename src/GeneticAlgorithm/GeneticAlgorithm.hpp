#include "PopElement.cpp"
#include <iostream>
#include <string>
#include <vector>

#ifndef GENETIC_ALGORITHM
#define GENETIC_ALGORITHM

class GeneticAlgorithm {
public:
  GeneticAlgorithm(int popSize, int numGenerations, int numGenes,
                   long double (*fitness)(std::vector<long double>),
                   long double minValue, long double maxValue,
                   long double mutationRate, long double mutationParam,
                   int kTournament, std::string Crossover);
  void showBestSolution();
  void run();

private:
  PopElement bestAns;
  std::vector<PopElement> pop, parents;
  long double minValue, maxValue, mutationRate, mutationParam;
  int popSize, numGenerations, numGenes, kTournament;
  long double (*fitness)(std::vector<long double>);
  std::vector<std::vector<long double>> (GeneticAlgorithm::*crossover)(int,
                                                                       int);

  void startPop();
  void evalPop();
  PopElement tournamentSelection();
  void parentsSelection();
  std::vector<std::vector<long double>> onePointCrossover(int p1, int p2);
  std::vector<std::vector<long double>> twoPointsCrossover(int p1, int p2);
  void createNewGeneration();
  long double checkNewValue(long double newValue);
  void uniformMutation();
  void showBestAns();

  long double uniformRandomNum(long double MinValue, long double MaxValue);
  std::vector<long double> uniformVectorRandomNum(int size);
};
#endif

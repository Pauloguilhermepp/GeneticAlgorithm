#include <iostream>
#include <vector>

#ifndef ELEMENT
#define ELEMENT

class PopElement {
public:
  PopElement();
  PopElement(int NumGenes, std::vector<long double>);
  void setVector(std::vector<long double> Vector);
  std::vector<long double> getVector();
  void setFitness(long double (*fitness)(std::vector<long double>));
  long double getFitness();

private:
  int numGenes;
  std::vector<long double> vector;
  long double fitness;
};
#endif

#include "PopElement.hpp"

PopElement::PopElement(){}

PopElement::PopElement(int NumGenes, std::vector<long double> Vector){
    numGenes = NumGenes;
    vector = Vector;
}

void PopElement::setVector(std::vector<long double> Vector){
    vector = Vector;
}

std::vector<long double> PopElement::getVector(){
    return vector;
}

void PopElement::setFitness(long double (*Fitness)(std::vector<long double>)){
    fitness = Fitness(vector);
}

long double PopElement::getFitness(){
    return fitness;
}

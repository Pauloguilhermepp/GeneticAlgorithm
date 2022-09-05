#include "GeneticAlgorithm/GeneticAlgorithm.cpp"

long double fitness(std::vector<long double> vector){
    long double sum = 0;

    for(int i = 0; i < vector.size(); i++){
        sum += vector[i];
    }

    return sum;
}

int main(){
    GeneticAlgorithm ga(50, 100, 5, &fitness, 0, 1, 1, 0.4, 8, "twoPoints");
    ga.run();

    return 0;
}
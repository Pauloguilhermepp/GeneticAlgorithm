#include "GeneticAlgorithm.hpp"

GeneticAlgorithm::GeneticAlgorithm(int PopSize, int NumGenerations,
                int NumGenes, long double (*Fitness)(std::vector<long double>),
                long double MinValue, long double MaxValue, long double MutationRate,
                long double MutationParam, int KTournament, std::string Crossover){
                    srand(time(NULL));
                    popSize = PopSize;
                    numGenerations = NumGenerations;
                    numGenes = NumGenes;
                    fitness = Fitness;
                    minValue = MinValue;
                    maxValue = MaxValue;
                    mutationRate = MutationRate;
                    mutationParam = MutationParam;
                    kTournament = KTournament;

                    if(Crossover == "onePoint"){
                        crossover = &GeneticAlgorithm::onePointCrossover;
                    }else if(Crossover == "twoPoints"){
                        crossover = &GeneticAlgorithm::twoPointsCrossover;
                    }else{
                        std::cout << "Crossover not valid!" << std::endl;
                        abort();
                    }
}

void GeneticAlgorithm::startPop(){
    for(int i = 0; i < popSize; i++){
        PopElement el(numGenes, uniformVectorRandomNum(numGenes));
        pop.push_back(el);
    }
}

void GeneticAlgorithm::evalPop(){
    for(int i = 0; i < popSize; i++){
        pop[i].setFitness(fitness);

        if(pop[i].getFitness() > bestAns.getFitness()){
            bestAns = pop[i];
        }
    }
}

PopElement GeneticAlgorithm::tournamentSelection(){
    int parent, opponent;

    for(int i = 0; i < popSize; i++){
        parent = (int)((double)rand() / RAND_MAX * (popSize));

        for(int j = 0; j < kTournament; j++){
            opponent = (int)((double)rand() / RAND_MAX * (popSize));
            if(pop[parent].getFitness() <  pop[opponent].getFitness()){
                parent = opponent;
            }
        }
    }

    return pop[parent];
}

void GeneticAlgorithm::parentsSelection(){
    for(int i = 0; i < popSize; i++){
        parents.push_back(tournamentSelection());
    }
}

std::vector<std::vector<long double>> GeneticAlgorithm::onePointCrossover(int pos1, int pos2){
    std::vector<long double> d1, d2, p1, p2;
    std::vector<std::vector<long double>> descendants;
    int ptc = (int)((double)rand() / RAND_MAX * (numGenes));

    p1 = parents[pos1].getVector();
    p2 = parents[pos2].getVector();

    d1.reserve(numGenes);
    d2.reserve(numGenes);

    d1.insert( d1.end(), p1.begin(), p1.begin() + ptc);
    d1.insert( d1.end(), p2.begin() + ptc, p2.end());

    d2.insert( d2.end(), p2.begin(), p2.begin() + ptc);
    d2.insert( d2.end(), p1.begin() + ptc, p1.end());

    descendants.push_back(d1);
    descendants.push_back(d2);

    return descendants;
}

std::vector<std::vector<long double>> GeneticAlgorithm::twoPointsCrossover(int pos1, int pos2){
    std::vector<long double> d1, d2, p1, p2;
    std::vector<std::vector<long double>> descendants;
    int ptc1, ptc2, ptc;
    ptc1 = (int)((double)rand() / RAND_MAX * (numGenes));
    ptc2 = (int)((double)rand() / RAND_MAX * (numGenes));

    if(ptc1 > ptc2){
        ptc = ptc1;
        ptc1 = ptc2;
        ptc2 = ptc;
    }

    p1 = parents[pos1].getVector();
    p2 = parents[pos2].getVector();

    d1.reserve(numGenes);
    d2.reserve(numGenes);

    d1.insert( d1.end(), p1.begin(), p1.begin() + ptc1);
    d1.insert( d1.end(), p2.begin() + ptc1, p2.begin() + ptc2);
    d1.insert( d1.end(), p1.begin() + ptc2, p1.end());

    d2.insert( d2.end(), p2.begin(), p2.begin() + ptc1);
    d2.insert( d2.end(), p1.begin() + ptc1, p1.begin() + ptc2);
    d2.insert( d2.end(), p2.begin() + ptc2, p2.end());

    descendants.push_back(d1);
    descendants.push_back(d2);

    return descendants;
}

void GeneticAlgorithm::createNewGeneration(){
    std::vector<std::vector<long double>> descendants;

    pop[0] = bestAns;
    pop[1] = bestAns;

    for(int i = 2; i < popSize; i += 2){
        descendants = ((*this).*crossover)(i, i+1);

        pop[i] = PopElement(numGenes, descendants[0]);
        pop[i+1] = PopElement(numGenes, descendants[1]);

    }
}

void GeneticAlgorithm::uniformMutation(){
    int mutationGenePos;
    std::vector<long double> vec;

    for(int i = 0; i < popSize; i++){
        if(((double)rand() / RAND_MAX) < mutationRate){
            mutationGenePos = (int)((double)rand() / RAND_MAX * (numGenes));

            vec = pop[i].getVector();
            vec[mutationGenePos] = uniformRandomNum(vec[mutationGenePos] - mutationParam, 
                                                    vec[mutationGenePos] + mutationParam);

            if(vec[mutationGenePos] > maxValue){
                vec[mutationGenePos] = maxValue;
            }else if(vec[mutationGenePos] < minValue){
                vec[mutationGenePos] = minValue;
            }

            pop[i].setVector(vec);
        }

    }
}

void GeneticAlgorithm::showBestAns(){
    std::cout << "BetsAnsVector: ";
    for(int i = 0; i < numGenes; i++){
        std::cout << bestAns.getVector()[i] << " ";
    }

    std::cout << std::endl;
    std::cout << "BetsAnsFitness: " << bestAns.getFitness() << std::endl;
}

void GeneticAlgorithm::run(){
    bestAns = PopElement(numGenes, uniformVectorRandomNum(numGenes));
    bestAns.setFitness(fitness);

    startPop();

    evalPop();

    for(int i = 0; i < numGenerations; i++){
        parentsSelection();

        createNewGeneration();

        uniformMutation();

        evalPop();
    }

    showBestAns();
}

long double GeneticAlgorithm::uniformRandomNum(long double MinValue, long double MaxValue){
    double f = (double)rand() / RAND_MAX;
    return (long double)(MinValue + f * (MaxValue - MinValue));
}

std::vector<long double> GeneticAlgorithm::uniformVectorRandomNum(int size){
    std::vector<long double> randomNums;

    for(int i = 0; i < size; i++){
        randomNums.push_back(uniformRandomNum(minValue, maxValue));
    }

    return randomNums;
}

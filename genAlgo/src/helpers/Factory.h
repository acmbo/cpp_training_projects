#ifndef FACTORY_H
#define FACTORY_H


#include <vector>
#include <functional>
#include <stdexcept>

template<typename INDIVIDUUMTYP>
class Factory {
public:
    // Constructor
    Factory(int chromosomeSize, int populationSize, std::function<int()>); // last thing is a pointer to a function

    // Methods
    INDIVIDUUMTYP CreateIndividual();
    INDIVIDUUMTYP Mutation(INDIVIDUUMTYP individuum);
    INDIVIDUUMTYP Crossover(INDIVIDUUMTYP parent1, INDIVIDUUMTYP parent2);
    std::vector<INDIVIDUUMTYP> CreatePopulation();
    std::vector<INDIVIDUUMTYP> MutatePopulation(std::vector<INDIVIDUUMTYP> population);
    std::vector<INDIVIDUUMTYP> CrossoverPopulation(std::vector<INDIVIDUUMTYP> population);
    void setMutationFunction(std::function<INDIVIDUUMTYP (INDIVIDUUMTYP)> mutationFunction);
    void setCrossoverFunction(std::function<INDIVIDUUMTYP (INDIVIDUUMTYP, INDIVIDUUMTYP)> crossoverFunction);
    void setPopulationSize(int populationSize);

private:
    // Private members
    int chromosomeSize;
    int populationSize;
    bool mutationActivated = false;
    bool crossoverActivated = false;
    std::function<int()> chromosomeGeneratorFunction;
    std::function<INDIVIDUUMTYP (INDIVIDUUMTYP)> mutationFunction;
    std::function<INDIVIDUUMTYP (INDIVIDUUMTYP, INDIVIDUUMTYP)> crossoverFunction;
};


//#include "Factory.cpp" // include the implementation file


#endif // !FACTORY_H
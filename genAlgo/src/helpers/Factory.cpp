/*

// Implememtation with inheritance of Factory
#include <vector>
#include <functional>
#include "../helpers/miscFunc.h"
#include "../helpers/Factory.h"


template<typename INDIVIDUUMTYP>
class IndFactory: public Factory<INDIVIDUUMTYP>  {
public:

    std::function<int()> chromosomeGeneratorFunction;

    IndFactory(int chromosomeSize, int populationSize, std::function<int()> inputchromgenfunc):   // int (*inputchromgenfunc)(int, int)) :
            Factory<INDIVIDUUMTYP>(chromosomeSize, populationSize, inputchromgenfunc)  {
            this->chromosomeSize = chromosomeSize;
            this->populationSize = populationSize;
            this->chromosomeGeneratorFunction = inputchromgenfunc;
            }
            

    INDIVIDUUMTYP CreateIndividual() {
        std::function<int()> chromosomeGenerator = this->chromosomeGeneratorFunction;
        return INDIVIDUUMTYP(chromosomeGenerator);
    }

    INDIVIDUUMTYP Mutation(INDIVIDUUMTYP individuum) {
        if (!mutationActivated) {
            throw std::runtime_error("Mutation function not set.");
        }
        return mutationFunction(individuum);
    }

    INDIVIDUUMTYP Crossover(INDIVIDUUMTYP parent1, INDIVIDUUMTYP parent2) {
        if (!crossoverActivated) {
            throw std::runtime_error("Crossover function not set.");
        }
        return crossoverFunction(parent1, parent2);
    }

    std::vector<INDIVIDUUMTYP> CreatePopulation() {
        std::vector<INDIVIDUUMTYP> population;
        for (int i = 0; i < populationSize; i++) {
            population.push_back(CreateIndividual());
        }
        return population;
    }

    std::vector<INDIVIDUUMTYP> MutatePopulation(std::vector<INDIVIDUUMTYP> population) {
        std::vector<INDIVIDUUMTYP> mutatedPopulation;
        for (int i = 0; i < population.size(); i++) {
            mutatedPopulation.push_back(Mutation(population[i]));
        }
        return mutatedPopulation;
    }

    std::vector<INDIVIDUUMTYP> CrossoverPopulation(std::vector<INDIVIDUUMTYP> population) {
        std::vector<INDIVIDUUMTYP> crossoverPopulation;
        for (int i = 0; i < population.size() - 1; i += 2) {
            crossoverPopulation.push_back(Crossover(population[i], population[i+1]));
        }
        // If population size is odd, add the last individuum without crossover
        if (population.size() % 2 != 0) {
            crossoverPopulation.push_back(population[population.size()-1]);
        }
        return crossoverPopulation;
    }

    void setMutationFunction(std::function<INDIVIDUUMTYP (INDIVIDUUMTYP)> mutationFunction) {
        this->mutationFunction = mutationFunction;
        mutationActivated = true;
    }

    void setCrossoverFunction(std::function<INDIVIDUUMTYP (INDIVIDUUMTYP, INDIVIDUUMTYP)> crossoverFunction) {
        this->crossoverFunction = crossoverFunction;
        crossoverActivated = true;
    }

    void setPopulationSize(int populationSize) {
        this->populationSize = populationSize;
    }


private:
    int chromosomeSize;
    int populationSize;

    bool mutationActivated = false;
    bool crossoverActivated = false;

    std::function<INDIVIDUUMTYP (INDIVIDUUMTYP)> mutationFunction;
    std::function<INDIVIDUUMTYP (INDIVIDUUMTYP, INDIVIDUUMTYP)> crossoverFunction;
};

            
*/



// Classic instiation of class:
#include "../helpers/miscFunc.h"
#include "../helpers/Factory.h"



template<typename INDIVIDUUMTYP>
Factory<INDIVIDUUMTYP>::Factory(int chromosomeSize, int populationSize, std::function<int()> inputchromgenfunc) :   // alternative to std::function u can use function pointer:  int (*inputchromgenfunc)(int, int)) :
            chromosomeSize(chromosomeSize),
            populationSize(populationSize),
            chromosomeGeneratorFunction(inputchromgenfunc)
            {}
            
template<typename INDIVIDUUMTYP>
INDIVIDUUMTYP Factory<INDIVIDUUMTYP>::CreateIndividual() {
    std::function<int()> chromosomeGenerator = this->chromosomeGeneratorFunction;
    return INDIVIDUUMTYP(chromosomeGenerator);
}

template<typename INDIVIDUUMTYP>
INDIVIDUUMTYP Factory<INDIVIDUUMTYP>::Mutation(INDIVIDUUMTYP individuum) {
        if (!mutationActivated) {
            throw std::runtime_error("Mutation function not set.");
        }
        return mutationFunction(individuum);
    }

template<typename INDIVIDUUMTYP>
INDIVIDUUMTYP Factory<INDIVIDUUMTYP>::Crossover(INDIVIDUUMTYP parent1, INDIVIDUUMTYP parent2) {
        if (!crossoverActivated) {
            throw std::runtime_error("Crossover function not set.");
        }
        return crossoverFunction(parent1, parent2);
    }

template<typename INDIVIDUUMTYP>
std::vector<INDIVIDUUMTYP> Factory<INDIVIDUUMTYP>::CreatePopulation() {
        std::vector<INDIVIDUUMTYP> population;
        for (int i = 0; i < populationSize; i++) {
            population.push_back(CreateIndividual());
        }
        return population;
    }

template<typename INDIVIDUUMTYP>
std::vector<INDIVIDUUMTYP> Factory<INDIVIDUUMTYP>::MutatePopulation(std::vector<INDIVIDUUMTYP> population) {
        std::vector<INDIVIDUUMTYP> mutatedPopulation;
        for (int i = 0; i < population.size(); i++) {
            mutatedPopulation.push_back(Mutation(population[i]));
        }
        return mutatedPopulation;
    }

template<typename INDIVIDUUMTYP>
std::vector<INDIVIDUUMTYP> Factory<INDIVIDUUMTYP>::CrossoverPopulation(std::vector<INDIVIDUUMTYP> population) {
        std::vector<INDIVIDUUMTYP> crossoverPopulation;
        for (int i = 0; i < population.size() - 1; i += 2) {
            crossoverPopulation.push_back(Crossover(population[i], population[i+1]));
        }
        // If population size is odd, add the last individuum without crossover
        if (population.size() % 2 != 0) {
            crossoverPopulation.push_back(population[population.size()-1]);
        }
        return crossoverPopulation;
    }

template<typename INDIVIDUUMTYP>
void Factory<INDIVIDUUMTYP>::setMutationFunction(std::function<INDIVIDUUMTYP (INDIVIDUUMTYP)> mutationFunction) {
    this->mutationFunction = mutationFunction;
    mutationActivated = true;
}

template<typename INDIVIDUUMTYP>
void Factory<INDIVIDUUMTYP>::setCrossoverFunction(std::function<INDIVIDUUMTYP (INDIVIDUUMTYP, INDIVIDUUMTYP)> crossoverFunction) {
        this->crossoverFunction = crossoverFunction;
        crossoverActivated = true;
    }

template<typename INDIVIDUUMTYP>
void Factory<INDIVIDUUMTYP>::setPopulationSize(int populationSize) {
        this->populationSize = populationSize;
    }


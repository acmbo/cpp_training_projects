#include <iostream>

#include "helpers/Factory.h"
#include "helpers/IndividuumBlueprint.h"
#include "helpers/miscFunc.h"

//Create Individdum class from Blueprint. Ensure calucalteFitness() has implementation. 
template<int CHROMOSOMESIZE>
class Individuum: public IndividuumBlueprint<CHROMOSOMESIZE> {

    public:
        // Constructor sets each chromosome. loop through array of chromosome and call function wich is passed
        Individuum<CHROMOSOMESIZE>(const std::function<int()> &chromosomeGenerator):
            IndividuumBlueprint<CHROMOSOMESIZE>(chromosomeGenerator) 
            {
                setChromosomeGeneratorFunction(chromosomeGenerator);
                for(int i = 0; i<this->chromosomeSize; i++) {
                    this->chromosome[i] = this->chromosomeGeneratorFunction();  // This is only here possible. Cant create setter function outside of here
            }
        }

        void setChromosomeGeneratorFunction(const std::function<int()> chromosomeGenerator) {
            this->chromosomeGeneratorFunction = chromosomeGenerator;
        }

        int calculateFitness() {
            int fitness=0;
            for(int i=0; i<this->chromosomeSize;i++) {
                fitness += this->chromosome[i];
            }
            this->fitness = fitness;
            return fitness;
        }

        int getChromosomeSize() const {
            return this->chromosomeSize;
        }

        int getFitness() const {
            return this->fitness;
        }

        int getChromosomeAt(int index) {
            return this->chromosome[index];
        }

        // returns a pointer to the array
        int (&getChromosome())[CHROMOSOMESIZE] {
            return this->chromosome;

        // As alternative use std:array :
        /*
            class MyClass {
            public:
                std::array<int, 5>& getArray() {
                    return myArray;
                }

            private:
                std::array<int, 5> myArray{1, 2, 3, 4, 5};
            };

            int main() {
                MyClass obj;
                std::array<int, 5>& arr = obj.getArray();

                for (auto i : arr) {
                    std::cout << i << " ";
                }
                std::cout << std::endl;

                return 0;
            }
        */
    }

};


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



int main() {
    setRandomSeed();
    
    Individuum<6> test2(genFunc);
    test2.calculateFitness();
    
    for(int i=0; i < test2.getChromosomeSize(); i++) {
        std::cout << test2.getChromosomeAt(i);
    }
    
    std::cout << "\nFitness: ";
    std::cout << test2.getFitness() << std::endl;

    std::cout << "Chromsize: ";
    std::cout << test2.getChromosomeSize() << std::endl;
    
    // First implementation:
    Factory<Individuum<10>> factory(10, 50, genFunc);

    // Second implementation:  
    //IndFactory<Individuum<10>> indfactory(10, 50, genFunc);


    // Print out all Indiviuals
    std::vector<Individuum<10>> population = factory.CreatePopulation();
    for (auto& ind : population) {
        int (&arr)[10] = ind.getChromosome();
    
        std::cout << "Individuum from Factory: ";
        for (int i = 0; i < 10; i++) {
            std::cout << arr[i] << " ";
        }

        std::cout << "\n";
    }
}
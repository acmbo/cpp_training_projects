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

        int getChromosome(int index) const {
            return this->chromosome[index];
        }

};


int main() {
    setRandomSeed();
    
    Individuum<6> test2(genFunc);
    test2.calculateFitness();
    
    for(int i=0; i < test2.getChromosomeSize(); i++) {
        std::cout << test2.getChromosome(i);
    }
    
    std::cout << "\nFitness: ";
    std::cout << test2.getFitness() << std::endl;

    std::cout << "Chromsize: ";
    std::cout << test2.getChromosomeSize() << std::endl;
    
    // First implementation:
    Factory<Individuum<10>> factory(10, 50, genFunc);

    // Second implementation:  
    //IndFactory<Individuum<10>> indfactory(10, 50, genFunc);


    //std::vector<Individuum<10>> population = factory.CreatePopulation();
    //for (auto& ind : population) {
    //    std::cout << ind.ToString() << '\n';
    // }
}
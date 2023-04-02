#ifndef INDIVIDUUMBLUEPRINT_H
#define INDIVIDUUMBLUEPRINT_H

#include <functional>
#include <vector>
#include <array>
/*

template<int CHROMOSOMESIZE>
class IndividuumBlueprint {

    public:
        std::function<int()> chromosomeGeneratorFunction;

        //virtual int calculateFitness();

        IndividuumBlueprint(const std::function<int()>) {}  
        void setChromosomeGeneratorFunction(const std::function<int()>);
        int calculateFitness();
        int getChromosomeSize();
        int getFitness();
        int getChromosomeAt(int index);
        int (&getChromosome())[CHROMOSOMESIZE];

    protected:
        int fitness;
        int chromosome[CHROMOSOMESIZE];
        int chromosomeSize = CHROMOSOMESIZE;    
};

*/


class IndividuumBlueprint {

    public:
        std::function<int()> chromosomeGeneratorFunction;

        //virtual int calculateFitness();

        IndividuumBlueprint(const std::function<int()>, int) {}  
        //~IndividuumBlueprint();

        void setChromosomeGeneratorFunction(const std::function<int()>);
        int calculateFitness();
        int getChromosomeSize();
        int getFitness();
        int getChromosomeAt(int index);
        int* getChromosome();

    protected:
        int fitness;
        int* chromosome;
        int chromosomeSize;    
};

#endif // !INDIVIDUUMBLUEPRINT_H

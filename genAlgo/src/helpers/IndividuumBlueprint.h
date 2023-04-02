#ifndef INDIVIDUUMBLUEPRINT_H
#define INDIVIDUUMBLUEPRINT_H

#include <functional>
#include <vector>

/*
template<int CHROMOSOMESIZE>
class IndividuumBlueprint {

    public:
        //virtual int calculateFitness();

        int fitness;
        int chromosome[CHROMOSOMESIZE];
        int chromosomeSize = CHROMOSOMESIZE;


        IndividualBlueprint(const std::function<int()> & chromosomeGenerator) {
            //this.chromosomeGenerator = chromosomeGenerator;
            for(int i = 0; i<CHROMOSOMESIZE;i++) {
                this->chromosome[i] = chromosomeGenerator();
            }
        }
        
    private:
        std::function<int()> chromosomeGeneratorFunction;
        
};
*/

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

#endif // !INDIVIDUUMBLUEPRINT_H

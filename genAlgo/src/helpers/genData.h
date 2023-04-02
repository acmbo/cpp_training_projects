#ifndef GENDATA_H
#define GENDATA_H

#include <vector>
#include <functional>


template<int CHROMOSOMESIZE>
class IndividualBlueprint {
    public:
        int fitness;
        int chromosome[CHROMOSOMESIZE];
        int chromosomeSize = CHROMOSOMESIZE;
        
        std::function<int()> chromosomeGenerator;

        IndividualBlueprint(const std::function<int()> & chromosomeGenerator) {
            //this.chromosomeGenerator = chromosomeGenerator;
            for(int i = 0; i<CHROMOSOMESIZE;i++) {
                this->chromosome[i] = chromosomeGenerator();
            }
        }
};

#endif // !GENDATA_H

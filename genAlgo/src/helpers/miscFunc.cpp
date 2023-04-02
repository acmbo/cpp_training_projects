#include "../helpers/miscFunc.h"

void setRandomSeed() {
    time_t randSeed = (unsigned)time(0);
    srand(randSeed); 
}


int getRandomInt(int min_v=0, int max_v=1)  {

    max_v++;    // have to push the limit +1, because (int) operation always rounds down
    int range = max_v - min_v;

    if (range==0) { return min_v; }
    int randomN =  min_v + (rand() % range);   // Alternative formula: int r_best = (int)(((float) rand()/RAND_MAX) * (max_v-min_v)) + min_v; 
    return randomN;
}


int genFunc() {
    return getRandomInt();
}
#include <vector>
#include <iostream>
#include "../fooddata/recipe.h"
#include "../fooddata/datahelper.h"

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


DataHelper::DataHelper(std::vector<Recipe> recipes) {
    this->recipes = recipes;
}

DataHelper::~DataHelper() {}


Recipe DataHelper::getRandomRecipe() {
    int randomIndex = getRandomInt(0, this->recipes.size());
    return this->recipes[randomIndex];
}


Recipe* DataHelper::getRecipeById(unsigned int targetId) {
    long unsigned int vecsize = this->recipes.size();
    for (long unsigned int i=0; i < vecsize; i++)
    {
        if(this->recipes[i].getId()==targetId) { return &this->recipes[i]; }
    }
    return NULL;
}


unsigned int DataHelper::getIndexOfRecipeById(unsigned int targetId) {
    long unsigned int vecsize = this->recipes.size();
    for (long unsigned int i=0; i < vecsize; i++)
    {
        if(this->recipes[i].getId()==targetId) { return i; }
    }
    throw std::domain_error("Given Index not found in DataHelper Recipes vector");
}


bool DataHelper::removeRecipeById(unsigned int targetId) {
    unsigned int targetindex = this->getIndexOfRecipeById(targetId);
    std::size_t originaVectorLength = this->recipes.size();

    std::vector<Recipe>::iterator iter = this->recipes.begin() + targetindex;  // get Index on certain position : https://stackoverflow.com/questions/6935389/how-to-get-iterator-to-a-particular-position-of-a-vector
    this->recipes.erase(iter);

    if (this->recipes.size() == originaVectorLength) {return false;} // check if erase was sucessfull
    return true;
}


bool DataHelper::removeRecipe(Recipe targetRecipe) {
    return this->removeRecipeById(targetRecipe.getId());
}



bool DataHelper::addRecipe(Recipe recipe) {   
    if (recipe.checkIfValidRecipe()) 
    {
        this->recipes.push_back(recipe);
    }
    return true;
}


bool DataHelper::RecipeIdInData(unsigned int targetId) {
    for (Recipe r: this->recipes)
    {
        if (r.getId() == targetId) { return true; }
    }
    return false;
}


bool DataHelper::checkAllRecipesByValidity(std::vector<Recipe>* ResultVector) {

    std::vector<Recipe> tempresultvector;
    bool valid = true;

    for (Recipe r: this->recipes)
    {
        if (r.checkIfValidRecipe()) {continue;} 

        if (ResultVector == NULL) {return false;}

        tempresultvector.push_back(r);
        valid = false;
    }

    if (ResultVector != NULL) {
        *ResultVector = tempresultvector;
    }

    return valid;
}


bool DataHelper::removeInValidRecipes() {
    std::vector<Recipe> tempresultvector;
    this->checkAllRecipesByValidity(&tempresultvector);

    for (Recipe r: tempresultvector)
    {
        this->removeRecipe(r);
    }
    return true;
}

#include <vector>
#include "../fooddata/recipe.h"

#ifndef DATAHELPER_H
#define DATAHELPER_H

class DataHelper {

    public:
        DataHelper(std::vector<Recipe>);
        ~DataHelper();

        std::vector<Recipe> recipes; 
        
        Recipe getRandomRecipe();
        Recipe* getRecipeById(unsigned int targetId);
        Recipe getRecipeByConditions();

        unsigned int getIndexOfRecipeById(unsigned int);
        
        bool addRecipe(Recipe);
        bool removeRecipe(Recipe);
        bool removeRecipeById(unsigned int);
        bool RecipeIdInData(unsigned int targetId);
        bool checkAllRecipesByValidity(std::vector<Recipe>* ResultVector);   // Use Nullpointer if no Result is needed!
        bool removeInValidRecipes();
};


void setRandomSeed();
int getRandomInt(int, int);

#endif // !DATAHELPER_H
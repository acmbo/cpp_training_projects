#include "../fooddata/recipe.h"

Recipe::Recipe(
            unsigned int id,
            std::string name,
            std::string submit_date,
            std::string tags,
            std::string steps,
            std::string description,
            std::string ingredients,
            unsigned int n_steps,
            unsigned int n_ingredients,
            double time_minutes,
            double calories,
            double totalfat,
            double sodium,
            double protein,
            double saturatedFat,
            double carbohydrates)
{
    this->id = id;
    this->name = name;
    this->submit_date = submit_date;
    this->tags = tags;
    this->steps = steps;
    this->description = description;
    this->ingredients = ingredients;
    this->n_steps = n_steps;
    this->n_ingredients = n_ingredients;
    this->time_minutes = time_minutes;
    this->calories = calories;
    this->totalfat = totalfat;
    this->sodium = sodium;
    this->protein = protein;
    this->saturatedFat = saturatedFat;
    this->carbohydrates = carbohydrates;
}

bool Recipe::checkIfValidRecipe() {
    if (this->calories <= 0) 
    {
        return false;
    }
    return true;
}

unsigned int Recipe::getId() {
    return id;
} 

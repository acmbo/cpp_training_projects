#ifndef RECIPE_H
#define RECIPE_H

#include <string>

class Recipe {
    public:
        std::string name;
        std::string submit_date;
        std::string tags;
        std::string steps;
        std::string description;
        std::string ingredients;

        unsigned int n_steps;
        unsigned int n_ingredients;

        double time_minutes;
        double calories;
        double totalfat;
        double sodium;
        double protein;
        double saturatedFat;
        double carbohydrates;

        Recipe(
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
            double carbohydrates);
        
        bool checkIfValidRecipe();
        unsigned int getId();

    private:
        unsigned int id; // Unsingend ist effizienter als normales int?
        long contributor_id;

};


#endif // !1
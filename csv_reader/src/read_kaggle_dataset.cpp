#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <typeinfo> // for debugging

#include "fooddata/dataframe.h"
#include "fooddata/recipe.h"
#include "fooddata/datahelper.h"

// Nutzung von namespace best pratice?
using namespace std;


// Create dataframe
// Pass by reference, why not pass by pointer?
DataFrame read_csv_files(string &fpath, char delim = ',') 
{
    string line;
    DataFrame df;

    // function to read csv
    if (filesystem::exists(fpath)) 
    {
        fstream csvstream;
        csvstream.open(fpath, ios::in);

        if (csvstream.is_open()) {

            // Get Header
            getline(csvstream, line);

            stringstream ss(line);

            while (getline(ss, line, delim)) 
            {
                df.columns.push_back(line);
                df.columnlen ++;
            }


            // Get Data through getline and new stringstream
            while (getline(csvstream, line))
            {

                stringstream ss(line);
                vector<string> row;

                // Get row 
                while(getline(ss, line, delim))
                {
                    row.push_back(line);
                }
                df.data.push_back(row);
                df.size++;
            }
        }
    }
    else 
    {
        cout << "File does no exists";
    }
    return df;
}


/// @brief Replaces parts of a string wit new set of string
/// @param targetString Complete string to look substring in
/// @param from Substring which to replace.
/// @param to String to replace with.
/// @return true for sucess
bool replaceStr(string &targetString, const string &from, const string &to)
{
    size_t position = targetString.find(from);
    if (position ==  targetString.size()) { return false; } 
    targetString.replace(position, from.length(), to);
    return true;
}



// Data in cell of row is stored in a string of a list of values
// Structure : ['calories','total fat','sugar','sodium','protein','saturated fat','carbohydrates']
// Example in Row : [73.1, 1.0, 15.0, 0.0, 5.0, 3.0, 4.0]
vector<double> getNutritionValues(string csvinput) {
    
    string line;
    stringstream sstream(csvinput);
    char delim = ',';
    vector<double> nutritionvals;

    while(getline(sstream, line, delim))
    {
        if (line.find("[") != std::string::npos)        // if "[" not found
        {
            replaceStr(line, "[", "");
        }
        if (line.find("]") != std::string::npos)        // if "[" not found
        {
            replaceStr(line, "]", "");
        }
        nutritionvals.push_back(std::stod(line));
    }
    return nutritionvals;
}




int main() 
{

    setRandomSeed();

    //string fpath = "Recipes_RAW_Test.csv";
    string fpath = "originalData/RAW_recipes_delimitier.csv";

    DataFrame df = read_csv_files(fpath, ';');

    int vecSize = df.data.size();
    vector<Row> structvec;

    for (int i = 0; i < vecSize; i++)
    {
        Row row;

        row.name = df.data[i][0];
        row.id = std::stoi(df.data[i][1], nullptr, 16);
        row.time_minutes = std::stod(df.data[i][2], nullptr);
        row.contributor_id = std::stol(df.data[i][3], nullptr);
        row.submit_date = df.data[i][4];
        row.tags = df.data[i][5];
        row.nutrition = df.data[i][6]; 
        row.n_steps = std::stoi(df.data[i][7], nullptr, 16);
        row.steps = df.data[i][8];
        row.description = df.data[i][9];
        row.ingredients = df.data[i][10];
        row.n_ingredients = std::stoi(df.data[i][11], nullptr, 16);
        
        vector<double> temporaryNutrationalvalues = getNutritionValues(row.nutrition);
        row.calories = temporaryNutrationalvalues[0];
        row.totalfat = temporaryNutrationalvalues[1];
        row.sodium = temporaryNutrationalvalues[2];
        row.protein = temporaryNutrationalvalues[3];
        row.saturatedFat = temporaryNutrationalvalues[4];
        row.carbohydrates = temporaryNutrationalvalues[5];

        structvec.push_back(row);
    }
    

    std::vector<Recipe> recipes;
    for (Row row: structvec)
    {
        Recipe recipe = Recipe{
            row.id,
            row.name,
            row.submit_date,
            row.tags,
            row.steps,
            row.description,
            row.ingredients,
            row.n_steps,
            row.n_ingredients,
            row.time_minutes,
            row.calories,
            row.totalfat,
            row.sodium,
            row.protein,
            row.saturatedFat,
            row.carbohydrates
        };
        recipes.push_back(recipe);
    } 

    // Create datahelper and check for validity of data
    DataHelper dataHelper(recipes);
    dataHelper.removeInValidRecipes();


    cout << "Done" << endl;
    return 0;
}

/*
//--------EXAMPLE:-----------

setRandomSeed();

string fpath = "Recipes_RAW_Test.csv";

// Read csv Data as Dataframe
DataFrame df = read_csv_files(fpath, ';');

cout << "Dataframe Size: ";
cout << df.size << endl;

int vecSize = df.data.size();
vector<Row> structvec;

for (int i = 0; i < vecSize; i++)
{
    //cout << i << endl;
    //cout << typeid(df.data[i][1]).name() << endl;
    //cout << std::stoi(df.data[i][1], nullptr, 16) << endl; // Nullpointer?  What is intbase?

    Row row;

    row.name = df.data[i][0];
    row.id = std::stoi(df.data[i][1], nullptr, 16);
    row.time_minutes = std::stod(df.data[i][2], nullptr);
    row.contributor_id = std::stol(df.data[i][3], nullptr);
    row.submit_date = df.data[i][4];
    row.tags = df.data[i][5];
    row.nutrition = df.data[i][6]; 
    row.n_steps = std::stoi(df.data[i][7], nullptr, 16);
    row.steps = df.data[i][8];
    row.description = df.data[i][9];
    row.ingredients = df.data[i][10];
    row.n_ingredients = std::stoi(df.data[i][11], nullptr, 16);
    
    vector<double> temporaryNutrationalvalues = getNutritionValues(row.nutrition);
    row.calories = temporaryNutrationalvalues[0];
    row.totalfat = temporaryNutrationalvalues[1];
    row.sodium = temporaryNutrationalvalues[2];
    row.protein = temporaryNutrationalvalues[3];
    row.saturatedFat = temporaryNutrationalvalues[4];
    row.carbohydrates = temporaryNutrationalvalues[5];

    structvec.push_back(row);
}

// Create recipes vector for datahelper

std::vector<Recipe> recipes;
for (Row row: structvec)
{
    Recipe recipe = Recipe{
        row.id,
        row.name,
        row.submit_date,
        row.tags,
        row.steps,
        row.description,
        row.ingredients,
        row.n_steps,
        row.n_ingredients,
        row.time_minutes,
        row.calories,
        row.totalfat,
        row.sodium,
        row.protein,
        row.saturatedFat,
        row.carbohydrates
    };
    recipes.push_back(recipe);
} 

// Create datahelper and check for validity of data
DataHelper dataHelper(recipes);
cout << "Check for invalid recipes: ";

std::vector<Recipe> tempresultvector;
cout << dataHelper.checkAllRecipesByValidity(&tempresultvector) << endl;


cout << "Invalid Recipes:" << endl;
for(Recipe r: tempresultvector)
{
    cout << "Recipe: " + std::to_string(r.getId());
    cout << " Calories: ";
    cout << r.calories << endl;
}

Recipe temprec = dataHelper.getRandomRecipe();
Recipe* temprecpt = dataHelper.getRecipeById(2118449);
cout << temprecpt->name << endl;

cout << dataHelper.removeRecipeById(2118449) << endl;
temprecpt = dataHelper.getRecipeById(2118449);
cout << (temprecpt == NULL) << endl;

*/


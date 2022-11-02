#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <typeinfo> // for debugging

#include "dataframe.h"

// Nutzung von namespace best pratice?
using namespace std;




struct Row {
    string name;
    unsigned int id; // Unsingend ist effizienter als normales int?
    double time_minutes;
    long contributor_id;
    string submit_date;
    string tags;
    string nutrition;
    unsigned int n_steps;
    string steps;
    string description;
    string ingredients;
    unsigned int n_ingredients;
};


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

            // TO DO:
            // https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/
            // THIs Only gives seperated lines. Delimiter should be used only in header and not for data


            // Get Header
            getline(csvstream, line);

            stringstream ss(line);

            while (getline(ss, line, delim)) 
            {
                cout << line << endl;
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
        nutritionvals.push_back(stod(line));
    }
    return nutritionvals;
}





int main() 
{
    string fpath = "Recipes_RAW_Test.csv";

    DataFrame df = read_csv_files(fpath, ';');

    df.helloWorld();

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
        row.time_minutes = stod(df.data[i][2], nullptr);
        row.contributor_id = std::stol(df.data[i][3], nullptr);
        row.submit_date = df.data[i][4];
        row.tags = df.data[i][5];
        row.nutrition = df.data[i][6]; 
        row.n_steps = std::stoi(df.data[i][7], nullptr, 16);
        row.steps = df.data[i][8];
        row.description = df.data[i][9];
        row.ingredients = df.data[i][10];
        row.n_ingredients = std::stoi(df.data[i][11], nullptr, 16);
        
        structvec.push_back(row);
    }
    
    getNutritionValues(structvec[100].nutrition);

    return 0;
}


/* TO DOO Rmove [ from string in   getNutritionValues( [73.1
 1.0
 15.0
 0.0
 5.0
 3.0
 4.0]
*/

#ifndef DATAFRAME_H
#define DATAFRAME_H

#include <vector>
#include <string>

// Nutzung von namespace best pratice?
using namespace std;


class DataFrame {
    public:
        vector<string> columns;
        vector<vector<string>> data;
        int columnlen;
        int size = 0;

        void helloWorld();
};



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
    // values from nutrients
    double calories;
    double totalfat;
    double sodium;
    double protein;
    double saturatedFat;
    double carbohydrates;
};


#endif // !1
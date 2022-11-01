#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>

// Nutzung von namespace best pratice?
using namespace std;


class DataFrame {
    public:
        vector<string> columns;
        vector<vector<string>> data;
        int columnlen;
        int size = 0;
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
        cout<< "Here" << endl;

        fstream csvstream;

        csvstream.open(fpath, ios::in);

        if (csvstream.is_open()) {

            // TO DO:
            // https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/
            // THIs Only gives seperated lines. Delimiter should be used only in header and not for data


            // Get Header

            getline(csvstream, line);

            // WTF was macht stringstreamm
            // Woher weis c++ das line überschrieben wird
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
                cout << line << endl;

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

int example() 
{
    string fpath = "employees.csv";
    DataFrame data;
    
    data = read_csv_files(fpath, ',');

    cout << "Dataframe Size: ";
    cout << data.size;

    return 0;
}


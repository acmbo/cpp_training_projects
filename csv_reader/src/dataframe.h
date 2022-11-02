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


#endif // !1
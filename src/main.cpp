#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include "Graph.h"
using namespace std;

int main() {
    //open dataset (i haven't pushed it yet but it would be in this directory if it was pushed)
    ifstream dataset("archive/US_Accidents_March23.csv");
    if (!dataset) {
        cout << "Error opening file" << endl;
        return 2;
    }

    // reads the header and prints it
    string row1;
    getline(dataset, row1);
    cout << row1 << endl;

    // reads the selected column and prints it
    string line;
    while (getline(dataset, line)) {
        stringstream ss(line);
        string column;
        int columnIndex = 0;
        while (getline(ss, column, ',')) {
            if (columnIndex == 4) {   // change the number to select a different column
                cout << column << endl;
            }
            columnIndex++;
        }
    }


}

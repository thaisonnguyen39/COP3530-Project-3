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
    //skip header
    getline(dataset, row1);
    //first line
    getline(dataset, row1);
    Entry entry1 = Entry(row1);
    entry1.printData();

}

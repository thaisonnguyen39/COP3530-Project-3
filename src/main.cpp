#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include "Graph.h"
using namespace std;

int main() {
    //open dataset (i haven't pushed it yet but it would be in this directory if it was pushed)
    ifstream dataset("archive/US_Accidents_March23.csv");
    if (!dataset) {
        cout << "Error opening file" << endl;
        return 2;
    }

}

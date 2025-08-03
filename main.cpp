#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include "Graph.h"
using namespace std;
vector<Entry> testLoad(ifstream& dataset) {
    vector<Entry> data;
    string row;
    //skip header
    getline(dataset, row);
    //state -> # of cases
    map<string,int> state_count;
    //go through whole dataset and pick at most 2000 cases from each state
    while (getline(dataset, row)) {
        Entry entry(row);
        int max_cases = 2000;
        if (state_count.find(entry.state) == state_count.end()) {
            state_count[entry.state] = 1;
            data.push_back(entry);
        }
        else if (state_count[entry.state] < max_cases) {
            state_count[entry.state]++;
            data.push_back(entry);
        }
    }
    //print out each state and its # of cases
    for (auto it = state_count.begin(); it != state_count.end(); it++) {
        cout << it->first << ": " << it->second << endl;
    }
    //return vector of entries
    return data;
}

int main() {
    //open dataset (i haven't pushed it yet but it would be in this directory if it was pushed)
    ifstream dataset("archive/US_Accidents_March23.csv");
    if (!dataset) {
        cout << "Error opening file" << endl;
        return 2;
    }
    vector<Entry> data = testLoad(dataset);
}

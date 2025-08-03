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
    //go through whole dataset and pick at most 2200 cases from each state
    while (getline(dataset, row)) {
        Entry entry(row);
        int max_cases = 2200;
        if (state_count.find(entry.state) == state_count.end()) {
            state_count[entry.state] = 1;
            data.push_back(entry);
        }
        else if (state_count[entry.state] < max_cases) {
            state_count[entry.state]++;
            data.push_back(entry);
        }
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

    // reads the header and prints it
    string row;
    //skip header
    getline(dataset, row);
    //first line
    getline(dataset, row);
    Entry entry1 = Entry(row);
    // entry1.printData();

    map<string, pair<int, int>> stateInfo;
    map<string, map<string, pair<int, int>>> adjList;
    vector<Entry> entries = testLoad(dataset);
    
    // Get the total severity and entry count for each state
    for (const auto& entry : entries) {
        stateInfo[entry.state].first+= entry.severity;
        stateInfo[entry.state].second++;
    }

    // Build the adjacency list
    for (size_t i = 0; i < entries.size(); ++i) {
        for (size_t j = i + 1; j < entries.size(); ++j) {
            if (entries[i].state != entries[j].state) {
                string state1 = entries[i].state;
                string state2 = entries[j].state;
                int total_severity = (entries[i].severity + entries[j].severity) / 2.0;

                // state1 to state2 edge
                adjList[state1][state2].first += total_severity;
                adjList[state1][state2].second++;

                // state2 to state1 edge
                adjList[state2][state1].first += total_severity;
                adjList[state2][state1].second++;
            }
        }
    }

    // Menu for the program
    int option;
    bool run = true;
    while (run) {
        cout << "Number and Severity of Accidents in the U.S." << endl;
        cout << "1. Input a state and get the average severity" << endl;
        cout << "2. Print Weighted Adjacency List" << endl;
        cout << "3. Option 3" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> option;

        // User inputs state abbreviation and gets the average severity
        if (option == 1) {
            string state;
            cout << "Enter state abbreviation (e.g, NY, TX): ";
            cin >> state;
            if (stateInfo.find(state) != stateInfo.end()) {
                double avgSeverity = static_cast<double>(stateInfo[state].first) / stateInfo[state].second;
                cout << "Average severity for " << state << ": " << avgSeverity << endl;
                cout << endl;
            } else {
                cout << "State not found." << endl;
                cout << endl;
            }
        }
        // Print the weighted adjacency list
        else if (option == 2) {
            cout << "Weighted Adjacency List: " << endl;
            for (const auto& [state, neighbors] : adjList) {
                cout << state << ": ";
                for (const auto& [neighbor, data] : neighbors) {
                    double avg = static_cast<double>(data.first) / data.second;
                    cout << "{" << neighbor << ", " << avg << "}, ";
                }
                cout << endl;
            }
        }
        else if (option == 0) {
            cout << "Exiting program." << endl;
            cout << endl;
            run = false;
        }
        else {
            cout << "Invalid option. Try again." << endl;
            cout << endl;
        }
    }
    return 0;
}


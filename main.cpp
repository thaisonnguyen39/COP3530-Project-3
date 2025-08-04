#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include "Graph.h"
using namespace std;
vector<Entry> loadFileData(ifstream& dataset, Graph &graph) {
    cout << "Loading database..." << endl;
    vector<Entry> data;
    string row;
    //skip header
    getline(dataset, row);
    //state -> # of cases
    map<string,int> state_count;
    //go through whole dataset and pick at most max_cases cases from each state
    int max_cases = INT_MAX;
    while (getline(dataset, row)) {
        Entry entry(row);
        if (state_count.find(entry.state) == state_count.end()) {
            state_count[entry.state] = 1;
            graph.insertTable(entry);
            data.push_back(entry);
        }
        else if (state_count[entry.state] < max_cases) {
            state_count[entry.state]++;
            graph.insertTable(entry);
            data.push_back(entry);
        }
    }
    //return vector of entries
    cout << "Database loaded." << endl;
    return data;
}
int main() {
    int cow;;
    //open dataset (i haven't pushed it yet but it would be in this directory if it was pushed)
    ifstream dataset("archive/US_Accidents_March23.csv");
    if (!dataset) {
        cout << "Error opening file." << endl;
        return 2;
    }
    cout << "File opened." << endl;

    Graph graph;
    map<string, pair<int, int>> stateInfo;
    map<string, map<string, pair<int, int>>> adjList;
    vector<Entry> entries = loadFileData(dataset, graph);
    
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
        cout << "3. Find traffic data within a state" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice:";

        string input;
        cin >> input;
        try {
            option = stoi(input);
        }
        catch (std::invalid_argument& e) {
            cout << "Invalid option. Try again." << endl << endl;
            continue;
        }

        // User inputs state abbreviation and gets the average severity
        if (option == 1) {
            string state;
            cout << "Enter state abbreviation (e.g, NY, TX):";
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
        else if (option == 3) {
            graph.startMenu();
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
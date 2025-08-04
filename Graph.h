#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <fstream>
#pragma once
#define INT_MAX 2147483647
using namespace std;

//Stores relevant data from each entry
struct Entry{
    int severity;
    long double start_lat;
    long double start_lng;
    //database doesn't always have end_lat and end_lng values, so we initialize them with an out of bounds number
    int ID;
    string description;
    string street;
    string city;
    string county;
    string state;
    string zip;
    Entry()=default;
    Entry(string line);
    void printData();
};
//Stores
struct Edge {
    Entry from;
    Entry to;
    long double weight; //distance between two cases
    Edge()=default;
    Edge(Entry &from, Entry &to, long double weight);
};
class Graph {
    map<string, vector<Entry>> state_table; //collection of entries, sorted by state
public:
    Graph()=default;
    long double getWeight(Entry from, Entry to);
    void insertTable(Entry entry);
    vector<Edge> buildGraph(string state);
    Entry buildGraphHelper(Entry new_vertex, Entry home_vertex, vector<Edge> &graph);
    void startMenu();
    void caseDataMenu(string state, vector<Edge> &edge_list);
    void printCaseDetails(string state, vector<Edge> &edge_list);
};


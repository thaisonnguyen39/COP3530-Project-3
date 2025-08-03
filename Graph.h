#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#define OOB 200
#pragma once
using namespace std;

//Struct stores relevant data from each entry
struct Entry{
  int severity;
  double start_lat;
  double start_lng;
  //database doesn't always have end_lat and end_lng values, so we initialize them with an out of bounds number
  double end_lat = OOB;
  double end_lng = OOB;
  string description;
  string street;
  string city;
  string county;
  string state;
  string zip;
    Entry(string line);
    void printData();
};




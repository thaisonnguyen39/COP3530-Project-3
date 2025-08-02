#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#pragma once
using namespace std;

struct Entry{
  string ID;
  string source;
  int severity;
  string start_time;
  string end_time;
  double start_lat;
  double start_lng;
  double end_lat;
  double end_lng;
  double distance;
  string description;
  string street;
  string city;
  string county;
  string state;
  string zip;
  string country;
  string timezone;
  string airport_code;
  string weather_time;
  float temperature;
  float wind_chill;
  float humidity;
  float pressure;
  float visibility;
  string wind_direction;
  float wind_speed;
  float precipitation;
  string weather_condition;
  bool amenity;
  bool bump;
  bool crossing;
  bool give_way;
  bool junction;
  bool no_exit;
  bool railway;
  bool roundabout;
  bool station;
  bool stop;
  bool traffic_calming;
  bool traffic_signal;
  bool turning_loop;
  string sunrise_sunset;
  string civil_twilight;
  string nautical_twilight;
  string astronomical_twilight;
    Entry(string line){
      istringstream iss(line);
      string temp;
      //Find some way to add all this data to the struct variables
    }
};




#include "Graph.h"

//parameterized constructor parses a line and stores them in variables
Entry::Entry(string line){
    istringstream iss(line);
    string temp;
    for (int column_index = 0; column_index < 17; column_index++) {
        getline(iss, temp, ',');
       if(!temp.empty()){
           switch (column_index) {
               case 2:
                   this->severity = stoi(temp);
               break;
               case 5:
                   this->start_lat = stod(temp);
               break;
               case 6:
                   this->start_lng = stod(temp);
               break;
               case 7:
                   this->end_lat = stod(temp);
               break;
               case 8:
                   this->end_lng = stod(temp);
               break;
               case 10:
                   this->description = temp;
               break;
               case 11:
                   this->street = temp;
               break;
               case 12:
                   this->city = temp;
               break;
               case 13:
                   this->county = temp;
               break;
               case 14:
                   this->state = temp;
               break;
               case 15:
                   this->zip = temp;
               break;
               default:
                   break;
           }
       }
    }
}

//prints out the entry's variables
void Entry::printData(){
  cout << "Severity: " << this->severity << endl;
  cout << "Start Latitude: " << this->start_lat << endl;
  cout << "Start Longitude: " << this->start_lng << endl;
  //checking if end_lat and end_lng have been initialized
  if(end_lat != OOB){
      cout << "End Latitude: " << this->end_lat << endl;
  }
  if(end_lng != OOB){
      cout << "End Longitude: " << this->end_lng << endl;
  }
  cout << "Description: " << this->description << endl;
  cout << "Street ID: " << this->street << endl;
  cout << "City: " << this->city << endl;
  cout << "County: " << this->county << endl;
  cout << "State: " << this->state << endl;
  cout << "Zip: " << this->zip << endl;
 }
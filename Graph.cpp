#include "Graph.h"
#include <sstream>
//parameterized constructor parses a line from the database and stores the data in member variables
Entry::Entry(string line){
    istringstream iss(line);
    string temp;
    for (int column_index = 0; column_index < 17; column_index++) {
        getline(iss, temp, ',');
       if(!temp.empty()){
           switch (column_index) {
               case 0:
                   this->ID = stoi(temp.substr(2,temp.size()-1));
               break;
               case 2:
                   this->severity = stoi(temp);
               break;
               case 5:
                   this->start_lat = stold(temp);
               break;
               case 6:
                   this->start_lng = stold(temp);
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
//prints an entry's details
void Entry::printData(){
    cout << "ID: " << this->ID << endl;
    cout << "Severity: " << this->severity << endl;
    cout << "Start Latitude: " << this->start_lat << endl;
    cout << "Start Longitude: " << this->start_lng << endl;
    cout << "Description: " << this->description << endl;
    cout << "Street ID: " << this->street << endl;
    cout << "City: " << this->city << endl;
    cout << "County: " << this->county << endl;
    cout << "State: " << this->state << endl;
    cout << "Zip: " << this->zip << endl;
}
//prints out the entry's variables
Edge::Edge(Entry &from, Entry &to, long double weight) {
    this->from = from;
    this->to = to;
    this->weight = weight;
}
//uses locational data with a distance formula to find the distance between two traffic cases
long double Graph::getWeight(Entry from, Entry to) {
    return sqrt(pow(to.start_lat - from.start_lat, 2) + pow(to.start_lng - from.start_lng, 2));
}
//inserts a traffic case to its respective vector in the table
void Graph::insertTable(Entry entry) {
    this->state_table[entry.state].push_back(entry);
}
//takes the state's case table data and returns a graph implemented as an edge list
vector<Edge> Graph::buildGraph(string state) {
    vector<Edge> graph; //vector of edges, each entry contains a pair<first, second> and a weight
    vector<Entry> state_data = state_table[state];
    Entry home_vertex = state_data[0];
    //for each entry
    for (int i = 1; i < state_data.size(); i++) {
        Entry new_vertex = state_data[i];
        home_vertex = buildGraphHelper(new_vertex, home_vertex, graph);
    }
    return graph;
}
//helper for buildGraph function
Entry Graph::buildGraphHelper(Entry new_vertex, Entry home_vertex, vector<Edge> &graph) {
    //initialize a minimum weight to potentially find a new minimum
    long double start_weight = getWeight(home_vertex, new_vertex);
    long double min_weight = start_weight;
    Entry new_home;
    //iterates over the current size of the graph to check for a new minimum weight
    for (int j = 0; j < graph.size(); j++) {
        if (graph[j].from.ID == home_vertex.ID || graph[j].to.ID == home_vertex.ID) {
            //check if distance(new_vertex, some neighbor of home_vertex) < distance(new_vertex, home_vertex)
            long double test_weight = getWeight(new_vertex, graph[j].to);
            //if found, set new minimum
            if (test_weight < min_weight) {
                new_home = graph[j].to;
                min_weight = test_weight;
            }
        }
    }
    //if no new minimum is found, add edge and return the home vertex to be used for the next function call
    if (min_weight == start_weight) {
        Edge new_edge(home_vertex, new_vertex, min_weight);
        graph.push_back(new_edge);
        return home_vertex;
    }
    //if a new minimum is found, recursively call function on the neighboring node
    return buildGraphHelper(new_vertex, new_home, graph);
}
//Arguments given by caseDataMenu
//User enters a case ID, then case details and nearby cases are printed
void Graph::printCaseDetails(string state, vector<Edge> &edge_list) {
    int ID;
    vector<Entry> nearby_cases;
    Entry current_case;
    bool found_case = false;
    cout << "Enter the case's ID:";
    cin >> ID;
    for (int i = 0; i < state_table[state].size(); i++) {
        if (state_table[state][i].ID == ID) {
            current_case = state_table[state][i];
            found_case = true;
        }
    }
    if (!found_case) {
        cout << "Error: invalid ID" << endl;
    }
    else {
        current_case.printData();
        for (Edge edge : edge_list) {
            if (edge.from.ID == ID)
                nearby_cases.push_back(edge.to);
        }
        if (nearby_cases.empty())
            cout << "No nearby cases" << endl;
        else {
            cout << "# of nearby cases: " << nearby_cases.size() << endl;
            for (Entry entry : nearby_cases) {
                cout << "ID: " << entry.ID << " - " << "Description: " << entry.description << endl;
            }
        }
    }
}
//sub-menu for individual state data
void Graph::startMenu() {
    bool found = false;
    string state;
    while (!found) {
        cout << "\nType \"help\" for a list of states\n"
                "Type \"back\" to return to main menu\n"
                "Enter a state's abbreviation:";
        cin >> state;
        //prints out list of available state abbreviations
        if (state == "help") {
            cout << "List of valid states: " << endl;
            int counter = 0;
            int line_size = 10;
            for (auto it = state_table.begin(); it != state_table.end(); it++) {
                cout << it->first << " ";
                counter++;
                if (counter == line_size) {
                    counter = 0;
                    cout << endl;
                }
            }
            cout << endl;
        }
        //returns back to main menu
        else if (state == "back")
            return;
        //if the state entered does not exist
        else if (this->state_table.find(state) == this->state_table.end())
            cout << "Invalid state input." << endl;
        //if the state's data has been found in the table
        else {
            found = true;
        }
    }
    cout << "Loading " << state << " case data..." << endl;
    vector<Edge> edge_list = buildGraph(state);
    if (!edge_list.empty()) {
        cout << state << " case data successfully loaded." << endl;
        caseDataMenu(state, edge_list);
    }
    else {
        cout << "Error: " << state << " data could not be loaded." << endl;
    }
}
void Graph::caseDataMenu(string state, vector<Edge> &edge_list) {
    int option;
    bool back = false;
    while (!back) {
        cout << "\n1. List all state cases \n"
                "2. View a case's details\n"
                "3. Return to main menu\n";
        cout << "Enter choice:";
        cin >> option;
        switch (option) {
            case 1: {
                //list all of a state's cases
                cout << "Number of cases: " << state_table[state].size() << endl;
                int counter = 0;
                int check_limit= 100;
                string check_option;
                for (Entry entry : state_table[state]) {
                    cout << "ID: " << entry.ID << " - " << "Description: " << entry.description << endl;
                    counter++;
                    if (counter == check_limit) {
                        cout << "View more cases? Enter Y to continue or any other character to stop:" << endl;
                        cin >> check_option;
                        if (check_option == "Y" || check_option == "y") {
                            counter = 0;
                            continue;
                        }
                        cout << "Ending cases display." << endl;
                        break;
                    }
                }
                break;
            }
            case 2: {
                printCaseDetails(state, edge_list);
                break;
            }
            case 3: {
                back = true;
                cout << endl;
                break;
            }
            default: {
                cout << "Invalid input." << endl;
                cin.clear();
                cin.ignore(INT_MAX, '\n'); //clears cin buffer
                break;
            }
        }
    }
}
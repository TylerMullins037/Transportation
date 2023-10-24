// main.cpp
#include "transportation_network.h"
#include <iostream>
#include <map>

using namespace std;

int main() {
    // Create a map to store cities and their connections
    map<string, City> cities;

    // Add cities and connections (you can 4populate this part)
    

    addConnection(cities, "Astora", "Heide", 700, false); 
    addConnection(cities, "Astora", "The Ringed City", 800, false);

    addConnection(cities, "Astora", "Anor Londo", 400, false);
    addConnection(cities, "Astora", "Thoroland", 300, false);
    addConnection(cities, "Thoroland", "Carim", 200, false);

    addConnection(cities, "Carim", "Vinheim", 200, false);
    addConnection(cities, "Vinheim", "Undead Asylum", 300, false);
    addConnection(cities, "Anor Londo", "Undead Asylum", 200, false);

    addConnection(cities, "Anor Londo", "Oolacile", 700, false);




    addConnection(cities, "Heide", "Unnamed Eastern Lands", 900, false);   
    addConnection(cities, "Olaphis", "Unnamed Eastern Lands", 1000, false);
    addConnection(cities, "Olaphis", "Heide", 1200, false);   
  
    addConnection(cities, "Unnamed Eastern Lands", "Far East", 1000, false); 

    addConnection(cities, "Oolacile", "The Ringed City", 450, false);
 



    addConnection(cities, "Vinheim", "Berenike", 700, false);

     
 
    addConnection(cities, "Berenike", "Balder", 150, false);
    addConnection(cities, "Oolacile", "Balder", 650, false);

    addConnection(cities, "Balder", "Undead Asylum", 650, false);
    
    addConnection(cities, "Five Finger Delta", "Catarina", 600, false);
    addConnection(cities, "The Great Swamp", "Five Finger Delta", 700, false);
    addConnection(cities, "Oolacile", "The Great Swamp", 700, false);
     addConnection(cities, "Catarina", "Berenike", 200, false);
   




    //addConnection(cities, "A", "B", 4, false);
    //addConnection(cities, "A", "C", 3, false);
    //addConnection(cities, "A", "E", 7, false);

    //addConnection(cities, "B", "D", 5, false);
    //addConnection(cities, "B", "C", 4, false);

    //addConnection(cities, "D", "G", 4, false);
    //addConnection(cities, "D", "E", 1, false);
    //addConnection(cities, "D", "F", 2, false);

    //addConnection(cities, "E", "F", 2, false);

    //addConnection(cities, "C", "G", 1, false);
    //addConnection(cities, "G", "H", 6, false);
    //addConnection(cities, "G", "F", 1, false);
    //addConnection(cities, "F", "H", 5, false);
    //addConnection(cities, "C", "H", 5, false);
 

    

    // Add more connections as needed

    // Example usage of shortestPath function
    string start = "Catarina";
        string end = "Far East";
    vector<string> path = shortestPath(cities, start, end);

    // Output the shortest path
    cout << "Shortest Path: ";
    for (const string& city : path) {
        cout << city << " -> ";
    }
    cout << "End" << endl;

    // Example usage of citiesWithinDistance function
    vector<string> citiesWithinDist = citiesWithinDistance(cities, start, 15);

    // Output cities within a certain distance
    cout << "Cities within 15 units from StartCity: ";
    for (const string& city : citiesWithinDist) {
        cout << city << ", ";
    }
    cout << endl;

    // Example usage of findIsolatedCities function
    vector<string> isolatedCities = findIsolatedCities(cities);

    // Output isolated cities
    cout << "Isolated Cities: ";
    for (const string& city : isolatedCities)
    {
        cout << city << ", ";
    }
    return 0;
}

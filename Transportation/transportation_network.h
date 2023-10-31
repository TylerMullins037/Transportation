// transportation_network.h
#ifndef TRANSPORTATION_NETWORK_H
#define TRANSPORTATION_NETWORK_H

#include <string>
#include <map>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

struct City {
    string name;
    map<string, int> connections; // City name -> Distance
};

// Function to find the shortest path between two cities using Dijkstra's algorithm
vector<string> shortestPath(map<string, City>& cities, string startCity, string endCity);

// Function to add a connection between two cities
void addConnection(map<string, City>& cities, string city1, string city2, int distance, bool oneWay);

// Function to identify cities that can be reached within a certain distance
vector<string> citiesWithinDistance(map<string, City>& cities, string startCity, int maxDistance);

// Function to determine if there are any isolated cities
vector<string> findIsolatedCities(map<string, City>& cities);

// Function to display the map
void displayMap(map<string, City>& cities);

#endif // TRANSPORTATION_NETWORK_H
// transportation_network.cpp
#include "transportation_network.h"
#include <iostream>
#include <climits>

using namespace std;

// Helper function to find the city with the shortest distance
string findMinDistanceCity(map<string, City>& cities, map<string, int>& distances, set<string>& unvisited) {
    string minCity;
    int minDistance = INT_MAX;
    for (const auto& city : unvisited) {
        if (distances[city] < minDistance) {
            minDistance = distances[city];
            minCity = city;
        }
    }

    return minCity;
}

// Function to find the shortest path between two cities using Dijkstra's algorithm

vector<string> shortestPath(map<string, City>& cities, string startCity, string endCity) {
    map<string, int> distances;
    map<string, string> previous;
    set<string> unvisited;

    if (cities.find(startCity) == cities.end() || cities.find(endCity) == cities.end()) {
        throw invalid_argument("Start or end city not found in the network.");
    }

    for (const auto& pair : cities) {
        string city = pair.first;
        distances[city] = (city == startCity) ? 0 : INT_MAX;
        previous[city] = "";
        unvisited.insert(city);
    }

    // Remove isolated cities from the unvisited set
    vector<string> isolated = findIsolatedCities(cities);
    for (const string& isolatedCity : isolated) {
        unvisited.erase(isolatedCity);
    }

    while (!unvisited.empty()) {
        string currentCity = findMinDistanceCity(cities, distances, unvisited);
       
        unvisited.erase(currentCity);

        for (const auto& pair : cities[currentCity].connections) {
            string neighbor = pair.first;
            int distance = pair.second;

            int altDistance = distances[currentCity] + distance;

            if (altDistance < distances[neighbor]) {
                distances[neighbor] = altDistance;
                previous[neighbor] = currentCity;
            }
        }
    }

    // Reconstruct the path
    vector<string> path;
    string city = endCity;
    while (!previous[city].empty()) {
        path.push_back(city);
        city = previous[city];
    }
    path.push_back(startCity);
    reverse(path.begin(), path.end());

    int totalDistance = distances[endCity];
    cout << "Total Distance: " << totalDistance << endl;
    return path;
}


// Function to add a connection between two cities
void addConnection(map<string, City>& cities, string city1, string city2, int distance, bool oneWay) {
    if (distance < 0) {
        throw invalid_argument("Distance cannot be negative");
    }
    if (city1 == city2) {
        throw invalid_argument("Cannot add connection to itself");
    }
    cities[city1].connections[city2] = distance;
    if (!oneWay) {
        // If it's not a one-way connection, add the reverse connection.
        cities[city2].connections[city1] = distance;
    }
}

// Function to identify cities that can be reached within a certain distance
vector<string> citiesWithinDistance(map<string, City>& cities, string startCity, int maxDistance) {
    if (cities.find(startCity) == cities.end()) {
        throw invalid_argument("Start city not found in the network.");
    }

    if (maxDistance > 0) {

        vector<string> reachableCities;

        // Create a queue for breadth-first search
        queue<pair<string, int>> bfsQueue;

        // Initialize visited flag for all cities
        map<string, bool> visited;
        for (const auto& pair : cities) {
            visited[pair.first] = false;
        }

        // Add the start city to the queue
        bfsQueue.push({ startCity, 0 });
        visited[startCity] = true;

        // Perform breadth-first search
        while (!bfsQueue.empty()) {
            string currentCity = bfsQueue.front().first;
            int currentDistance = bfsQueue.front().second;
            bfsQueue.pop();

            // Check if the current city is within the specified distance
            if (currentDistance <= maxDistance) {
                reachableCities.push_back(currentCity);
                if (currentCity == startCity) {
                    reachableCities.pop_back();
                }

                // Explore neighboring cities
                for (const auto& neighborPair : cities[currentCity].connections) {
                    string neighborCity = neighborPair.first;
                    int neighborDistance = neighborPair.second;

                    // If the neighbor is not visited, add it to the queue
                    if (!visited[neighborCity]) {
                        bfsQueue.push({ neighborCity, currentDistance + neighborDistance });
                        visited[neighborCity] = true;
                    }
                }
            }
        }
        return reachableCities;
    }
    else {
        throw invalid_argument("Distance cannot be negative.");
    
    }
}

// Function to determine if there are any isolated cities
vector<string> findIsolatedCities(map<string, City>& cities) {
    vector<string> isolatedCities;

    for (const auto& pair : cities) {
        const string& cityName = pair.first;
        const map<string, int>& connections = pair.second.connections;

        // Check if the city has no outgoing connections
        bool isolated = connections.empty();

        if (isolated) {
            isolatedCities.push_back(cityName);
        }
    }

    return isolatedCities;
}


// Function to display the map
void displayMap(map<string, City>& cities) {
    if (!cities.empty()) {
        for (const auto& pair : cities) {
            const string& cityName = pair.first;
            const City& city = pair.second;

            cout << "City: " << cityName << endl;
            cout << "Connections:" << endl;
            for (const auto& connection : city.connections) {
                cout << "  To: " << connection.first << ", Distance: " << connection.second << endl;
            }
            cout << "-------------------------" << endl;
        }
    }
    else {
        throw invalid_argument("The cities map is empty");
    }
}
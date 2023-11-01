#include "transportation_network.h"
#include <iostream>
#include <map>

using namespace std;

int main() {
    // Create a map to store cities and their connections
    map<string, City> cities;

    // Add preset connections
    while (true) {
        cout << "Menu:\n";
        cout << "1. Use preset\n";
        cout << "2. Add a new connection\n";
        cout << "3. Add an isolated city\n";
        cout << "4. Find shortest path between cities\n";
        cout << "5. Find cities within a certain distance\n";
        cout << "6. Find isolated cities\n";
        cout << "7. Display Map\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        try {
            switch (choice) {
            
            case 1: {

                addConnection(cities, "Astora", "Heide", 700, false);
                addConnection(cities, "Astora", "The Ringed City", 800, false);
                addConnection(cities, "Astora", "Anor Londo", 400, false);
                addConnection(cities, "Astora", "Thoroland", 300, false);
                addConnection(cities, "Thoroland", "Carim", 200, false);
                addConnection(cities, "Carim", "Vinheim", 200, true);
                addConnection(cities, "Vinheim", "Undead Asylum", 300, false);
                addConnection(cities, "Anor Londo", "Undead Asylum", 200, false);
                addConnection(cities, "Anor Londo", "Oolacile", 700, false);
                addConnection(cities, "Heide", "Unnamed Eastern Lands", 900, false);
                addConnection(cities, "Olaphis", "Unnamed Eastern Lands", 1000, false);
                addConnection(cities, "Olaphis", "Heide", 1200, true);
                addConnection(cities, "Unnamed Eastern Lands", "Far East", 1000, false);
                addConnection(cities, "Oolacile", "The Ringed City", 450, false);
                addConnection(cities, "Vinheim", "Berenike", 700, false);
                addConnection(cities, "Berenike", "Balder", 150, false);
                addConnection(cities, "Oolacile", "Balder", 650, false);
                addConnection(cities, "Undead Asylum", "Balder", 650, true);
                addConnection(cities, "Five Finger Delta", "Catarina", 600, false);
                addConnection(cities, "The Great Swamp", "Five Finger Delta", 700, false);
                addConnection(cities, "Oolacile", "The Great Swamp", 700, false);
                addConnection(cities, "Catarina", "Berenike", 200, false);

                City newCity;
                newCity.name = "Zena";
                cities["Zena"] = newCity;
                cout << "Preset Cities added successfully.\n" << endl;
                break;
            }
            case 2: {
                string start, end;
                int distance;
                bool oneWay;
                cin.ignore();
                cout << "Enter the starting city: ";
                getline(cin, start);
                cout << "Enter the ending city: ";
                getline(cin, end);
                cout << "Enter the distance: ";
                cin >> distance;

                // Get the oneWay input and validate it
                cout << "Is it a one way connection? (1 for yes, 0 for no): ";
                cin >> oneWay;

                if (cin.fail() || (oneWay != 0 && oneWay != 1)) {
                    cout << "Invalid input. Please enter valid values.\n" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the error state and ignore invalid characters
                    break; // Exit this case
                }

                addConnection(cities, start, end, distance, oneWay);
                cout << "Connection added successfully.\n" << endl;
                break;
            }

            case 3: {
                string isolated;
                cin.ignore();
                cout << "Enter the isolated city: ";
                getline(cin, isolated);
                City newCity;
                newCity.name = isolated;
                cities[isolated] = newCity;
                cout << "Isolated City added successfully.\n" << endl;
                break;
            }
            case 4: {
                string start, end;
                cin.ignore(); // Clear the newline character from the previous input
                cout << "Enter the starting city: ";
                getline(cin, start);
                cout << "Enter the ending city: ";
                getline(cin, end);
                vector<string> path = shortestPath(cities, start, end);

                // Output the shortest path
                cout << "Shortest Path: ";
                for (const string& city : path) {
                    cout << city << " -> ";
                }
                cout << "End\n" << endl;
                break;
            }


            case 5: {
                string start;
                int distance;
                cin.ignore();
                cout << "Enter the city: ";
                getline(cin, start);
                cout << "Enter the maximum distance: ";
                cin >> distance;
                if (cin.fail()) {
                    cout << "Invalid input. Please enter a valid distance.\n" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the error state and ignore invalid characters
                    break; // Exit this case
                }
                vector<string> citiesWithinDist = citiesWithinDistance(cities, start, distance);
                // Output cities within a certain distance
                if (!citiesWithinDist.empty()) {
                    cout << citiesWithinDist[0]; // Print the first city without a comma
                    for (int i = 1; i < citiesWithinDist.size(); i++) {
                        cout << ", " << citiesWithinDist[i]; // Print a comma before other cities
                    }
                }
                else {
                    cout << "No Cities within distance";
                }
                cout << "\n" << endl;
                break;
            }
            case 6: {
                vector<string> isolatedCities = findIsolatedCities(cities);
                // Output isolated cities
                cout << "Isolated Cities: ";
                cout << isolatedCities[0];
                for (int i = 1; i < isolatedCities.size(); i++) {
                    cout << ", " << isolatedCities[i];
                }
                cout << "\n" << endl;
                break;
            }
            case 7: {

                displayMap(cities);
                break;
            }
            case 8:
                // Exit the program
                return 0;
            default:
                if (cin.fail()) {
                    cout << "Invalid input. Please enter a number on the menu\n" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the error state and ignore invalid characters
                    break; // Exit this case
                }
            }
        }
        catch (const invalid_argument& e) {
            cerr << "Error: " << e.what() <<"\n" << endl;
        }
    }

    return 0;
}

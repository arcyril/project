#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <functional>
#include "Accident.h"
#include "UniversalAlgorithm.h"

// Function to load the CSV file into our vector
void loadData(std::vector<Accident>& data, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filename << "\n";
        return;
    }

    std::string line;
    std::getline(file, line); // Skip the first line (headers)

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        Accident acc;
        int col = 0;

        // Read each value separated by a comma
        while (std::getline(ss, token, ',')) {
            try {
                if (col == 1) acc.collision_year = std::stoi(token);
                else if (col == 8) acc.collision_severity = static_cast<Severity>(std::stoi(token));
                else if (col == 9) acc.number_of_vehicles = std::stoi(token);
                else if (col == 10) acc.number_of_casualties = std::stoi(token);
                else if (col == 11) acc.date = token;
                else if (col == 13) acc.time = token;
                else if (col == 23) acc.junction_detail = static_cast<JunctionDetail>(std::stoi(token));
                else if (col == 31) acc.weather_conditions = static_cast<Weather>(std::stoi(token));
            } catch (...) {
                // Ignore any lines that have bad/empty numbers
            }
            col++;
        }
        data.push_back(acc);
    }
    file.close();
}

int main() {
    std::vector<Accident> allAccidents;
    UniversalAlgorithm algorithm;

    std::cout << "LOADING DATA\n";
    // Make sure these files are in the same directory where you run the executable!
    loadData(allAccidents, "dft-road-casualty-statistics-collision-2023.csv");
    loadData(allAccidents, "dft-road-casualty-statistics-collision-2024.csv");
    loadData(allAccidents, "dft-road-casualty-statistics-collision-provisional-2025.csv");
    
    std::cout << "LOADED " << allAccidents.size() << " accidents.\n";

    bool running = true;
    while (running) {
        std::cout << "\n FILTER BY?\n";
        std::cout << "1 - Filter by year-range\n";
        std::cout << "2 - Filter by minimum number of casualties\n";
        std::cout << "0 - Exit\n";
        std::cout << "TYPE A NUMBER: ";
        
        int choice;
        std::cin >> choice;

        if (choice == 0) {
            running = false;
        } 
        else if (choice == 1 || choice == 2) {
            std::vector<Accident> filteredAccidents;

            // Processor 1: Insert matching elements into the new vector
            auto procInsertInto = [&filteredAccidents](const Accident& acc) {
                filteredAccidents.push_back(acc);
            };

            // Setup our Predicate
            std::function<bool(const Accident&)> activePredicate;

            if (choice == 1) {
                int minYear, maxYear;
                std::cout << "STARTING YEAR: "; std::cin >> minYear;
                std::cout << "ENDING YEAR: "; std::cin >> maxYear;
                
                // predHappenedBetween implementation
                activePredicate = [minYear, maxYear](const Accident& acc) {
                    return (acc.collision_year >= minYear && acc.collision_year <= maxYear);
                };
            } 
            else if (choice == 2) {
                int minCasualties;
                std::cout << "MINIMUM NUMBER OF CASUALTIES: "; std::cin >> minCasualties;
                
                // predConditions implementation (using one specific condition for simplicity)
                activePredicate = [minCasualties](const Accident& acc) {
                    return acc.number_of_casualties >= minCasualties;
                };
            }

            // Apply filter using Universal Algorithm
            algorithm.process(allAccidents.begin(), allAccidents.end(), activePredicate, procInsertInto);

            // Predicate and Processor for Printing
            auto predTrue = [](const Accident&) { return true; }; // Always true
            
            auto procPrint = [](const Accident& acc) {
                std::cout << "[" << acc.date << " " << acc.time << "] "
                          << "Vehicles: " << acc.number_of_vehicles 
                          << " | Casualties: " << acc.number_of_casualties << "\n";
            };

            std::cout << "\nFILTERED RESULTS (" << filteredAccidents.size() << ") \n";
            // Print results using Universal Algorithm
            algorithm.process(filteredAccidents.begin(), filteredAccidents.end(), predTrue, procPrint);
        }
    }

    return 0;
}
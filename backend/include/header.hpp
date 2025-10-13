#ifndef HEADER_HPP
#define HEADER_HPP
#include <iostream>
#include <string>
#include "V.hpp"
#include <memory>
#include <vector>
#include <iomanip>

class DatabaseManager;

// Menu functions (simple)
void displayMainMenu();
int handleMenuChoice(DatabaseManager& database);
void showCityAndFood(DatabaseManager& database);

// Controller functions (delegated)
void showTripController(DatabaseManager& database);
void runTripTests(DatabaseManager& database);

namespace TripTypes {
    const std::string PARIS_TOUR = "paris_tour";
    const std::string LONDON_TOUR = "london_tour";
    const std::string CUSTOM_TOUR = "custom_tour";
    const std::string BERLIN_TOUR = "berlin_tour";
}

#endif
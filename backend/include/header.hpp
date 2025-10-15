/**
 * @file header.hpp
 * @brief Common header file with shared includes and utility functions
 */

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
 /**
  * @brief Display the main menu to the user
  * 
  * Shows the available options in the trip planning application.
  */
 void displayMainMenu();
 
 /**
  * @brief Handle user menu choice
  * @param database Reference to the database manager
  * @return The selected menu option
  * 
  * Processes user input and executes the corresponding menu action.
  */
 int handleMenuChoice(DatabaseManager& database);
 
 /**
  * @brief Show cities and their associated foods
  * @param database Reference to the database manager
  * 
  * Displays all cities along with their food recommendations.
  */
 void showCityAndFood(DatabaseManager& database);
 
 // Controller functions (delegated)
 /**
  * @brief Show trip controller interface
  * @param database Reference to the database manager
  * 
  * Handles the trip planning and management interface.
  */
 void showTripController(DatabaseManager& database);
 
 /**
  * @brief Run trip-related tests
  * @param database Reference to the database manager
  * 
  * Executes various tests related to trip functionality.
  */
 void runTripTests(DatabaseManager& database);
 
 /**
  * @namespace TripTypes
  * @brief Contains constants for different trip types
  * 
  * This namespace defines the available trip types in the system.
  */
 namespace TripTypes {
     const std::string PARIS_TOUR = "paris_tour";    ///< Paris tour trip type
     const std::string LONDON_TOUR = "london_tour";  ///< London tour trip type
     const std::string CUSTOM_TOUR = "custom_tour";  ///< Custom tour trip type
     const std::string BERLIN_TOUR = "berlin_tour";  ///< Berlin tour trip type
 }
 
 #endif
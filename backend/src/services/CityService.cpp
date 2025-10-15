/**
 * @file CityService.cpp
 * @brief Implementation of CityService class for city-related operations
 */

#include "../../include/services/CityService.hpp"
#include "../../include/repositories/CityRepository.hpp"
#include "../../include/services/FoodService.hpp"
#include <iostream>

// ============================================================================
// CONSTRUCTOR
// ============================================================================

/**
 * @brief Constructor implementation
 * @param cityRepo Reference to CityRepository instance
 * 
 * Initializes the city service with a city repository.
 * All city operations will be performed through this repository.
 */
CityService::CityService(CityRepository& cityRepo) : cityRepo(cityRepo) {
}

// ============================================================================
// PUBLIC METHODS
// ============================================================================

/**
 * @brief Get all cities from the database
 * @return Vector containing all City objects
 * 
 * Retrieves all cities from the database through the city repository.
 * This method acts as a service layer wrapper around the repository.
 */
V<City> CityService::getAllCities() {
    V<City> cities = cityRepo.findAll();  // Call the CityRepository method to get all cities
                                          // This returns a V<City> container with all cities from the database
    return cities;                         // Return all the City objects we found
}

/**
 * @brief Display all cities in a formatted view
 * 
 * Shows all cities from the database in a nicely formatted display.
 * Creates a header with decorative borders and lists all cities with their details.
 */
void CityService::displayAllCities() {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    // \n = new line
    // std::string(50, '=') = create a string with 50 equal signs
    // std::endl = end the line and move to next line

    std::cout << "                    ALL CITIES" << std::endl;

    std::cout << std::string(50, '=') << std::endl;
    // Print another line of equal signs

    // Get all cities from the database
    V<City> cities = getAllCities();  // Call our getAllCities() method to get all cities
                                      // This returns a V<City> container with all cities

    // Display each city
    for (int i = 0; i < cities.size(); i++) {
        // Loop through each city we got from the database
        // i starts at 0 and goes up to cities.size() - 1

        City city = cities[i];  // Get the current city from the container
                                // cities[i] gets the city at position i

        displayCity(city);      // Display this city
                                // Call our helper method to show the city
    }

    // Display footer - create a nice looking ending
    std::cout << std::string(50, '=') << std::endl;
    // Print another line of equal signs
}


/**
 * @brief Display cities with their associated foods
 * @param foodService Reference to FoodService for retrieving food data
 * 
 * Shows all cities along with their associated food recommendations.
 * For each city, displays the city name and lists all available foods with prices.
 * If no foods are available for a city, displays an appropriate message.
 */
void CityService::displayCitiesWithFood(FoodService& foodService) {

    // Get all cities from the database
    V<City> cities = getAllCities();

    // Display each city with its food
    for (int i = 0; i < cities.size(); i++) {
        City city = cities[i];

        // Display city name
        std::cout << "\n" << city.getName() << std::endl;
        std::cout << std::string(city.getName().length(), '-') << std::endl;

        // Get and display foods for this city
        V<Food> foods = foodService.getFoodsByCityId(city.getId());
        if (foods.size() > 0) {
            for (int j = 0; j < foods.size(); j++) {
                Food food = foods[j];
                std::cout << "  • " << food.getName() << " - $" << food.getPrice() << std::endl;
            }
        } else {
            std::cout << "  No foods available for this city" << std::endl;
        }
    }
}

/**
 * @brief Display a single city
 * @param city The City object to display
 * 
 * Shows the details of a single city in a simple format.
 * Currently displays only the city name.
 */
void CityService::displayCity(const City& city) {
    std::cout << city.getName() << std::endl;
    // Example output: Name: Paris"
}
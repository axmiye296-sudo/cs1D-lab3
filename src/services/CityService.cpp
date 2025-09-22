#include "../../include/services/CityService.hpp"
#include "../../include/repositories/CityRepository.hpp"
#include <iostream>


CityService::CityService(CityRepository& cityRepo) : cityRepo(cityRepo) {
}

// Method to get all cities from the database
V<City> CityService::getAllCities() {
    V<City> cities = cityRepo.findAll();  // Call the CityRepository method to get all cities
                                          // This returns a V<City> container with all cities from the database
    return cities;                         // Return all the City objects we found
}

// Method to display all cities on screen
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

void CityService::displayCity(const City& city) {
    std::cout << "ID: " << city.getId() << ", Name: " << city.getName() << std::endl;
    // Example output: "ID: 1, Name: Paris"
}
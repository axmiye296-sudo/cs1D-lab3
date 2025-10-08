/**
 * @file tripCityService.cpp
 * @brief Implementation of TripCityService class for managing trip-city relationships
 * @author CS1D Lab 3 Team
 * @date 2025
 * 
 * This file contains the business logic implementation for managing the relationship
 * between trips and cities, including adding, removing, and updating cities in trips.
 */

#include "../../include/services/tripCityService.hpp"
#include <iostream>
#include <iomanip> // Required for std::setw

/**
 * @brief Constructor for TripCityService
 * @param repository Reference to TripCityRepository for data access
 * 
 * Initializes the service with a repository instance for database operations.
 * The repository handles all direct database interactions while the service
 * provides business logic and validation.
 */
TripCityService::TripCityService(TripCityRepository& repository) : repo(repository) {}

/**
 * @brief Adds a city to a specific trip
 * @param tripId The ID of the trip to add the city to
 * @param cityId The ID of the city to add
 * @param visitOrder The order of visit (optional, auto-assigned if -1)
 * @return true if city was successfully added, false otherwise
 * 
 * This method handles the complete process of adding a city to a trip:
 * 1. Auto-assigns visit order if not provided
 * 2. Validates all parameters
 * 3. Checks if city already exists in trip
 * 4. Creates TripCity entity and saves to database
 * 
 * @note If visitOrder is -1, the method will automatically assign the next
 *       available visit order based on existing cities in the trip.
 */
bool TripCityService::addCityToTrip(int tripId, int cityId, int visitOrder) {
    if (visitOrder == -1) {
        visitOrder = getNextVisitOrder(tripId);
    }
    
    if (!validateTripCity(tripId, cityId, visitOrder)) {
        return false;
    }
    
    if (cityExistsInTrip(tripId, cityId)) {
        std::cout << "City " << cityId << " already exists in trip " << tripId << std::endl;
        return false;
    }
    
    TripCity tripCity(0, tripId, cityId, visitOrder);
    return repo.save(tripCity);
}

/**
 * @brief Retrieves all cities for a specific trip
 * @param tripId The ID of the trip
 * @return V<TripCity> Vector of TripCity objects for the trip
 * 
 * Returns all cities associated with the given trip ID, ordered by visit order.
 * If no cities are found, returns an empty vector.
 */
V<TripCity> TripCityService::getCitiesForTrip(int tripId) {
    return repo.findByTrip(tripId);
}

/**
 * @brief Removes a city from a specific trip
 * @param tripId The ID of the trip
 * @param cityId The ID of the city to remove
 * @return true if city was successfully removed, false if not found
 * 
 * Searches for the specified city in the trip and removes it if found.
 * The method iterates through all cities in the trip to find the matching city ID.
 */
bool TripCityService::removeCityFromTrip(int tripId, int cityId) {
    // Get all cities for this trip
    V<TripCity> cities = repo.findByTrip(tripId);
    
    // Find the city to remove
    for (const auto& city : cities) {
        if (city.getCityId() == cityId) {
            return repo.remove(city.getId());
        }
    }
    
    return false; // City not found in trip
}

/**
 * @brief Updates the visit order of a city in a trip
 * @param tripId The ID of the trip
 * @param cityId The ID of the city to update
 * @param newOrder The new visit order
 * @return true if visit order was successfully updated, false if city not found
 * 
 * Changes the visit order of a specific city within a trip. This affects
 * the sequence in which cities are visited during the trip.
 */
bool TripCityService::updateVisitOrder(int tripId, int cityId, int newOrder) {
    // Get all cities for this trip
    V<TripCity> cities = repo.findByTrip(tripId);
    
    // Find the city to update
    for (const auto& city : cities) {
        if (city.getCityId() == cityId) {
            TripCity updatedCity = city;
            updatedCity.setVisitOrder(newOrder);
            return repo.save(updatedCity);
        }
    }
    
    return false; // City not found in trip
}

/**
 * @brief Checks if a city exists in a specific trip
 * @param tripId The ID of the trip
 * @param cityId The ID of the city to check
 * @return true if city exists in trip, false otherwise
 * 
 * Performs a linear search through all cities in the trip to determine
 * if the specified city is already included.
 */
bool TripCityService::cityExistsInTrip(int tripId, int cityId) {
    V<TripCity> cities = repo.findByTrip(tripId);
    
    for (const auto& city : cities) {
        if (city.getCityId() == cityId) {
            return true;
        }
    }
    
    return false;
}

/**
 * @brief Gets the next available visit order for a trip
 * @param tripId The ID of the trip
 * @return int The next visit order number
 * 
 * Calculates the next visit order by finding the maximum existing visit order
 * and adding 1. This ensures cities are added in sequential order.
 */
int TripCityService::getNextVisitOrder(int tripId) {
    V<TripCity> cities = repo.findByTrip(tripId);
    
    int maxOrder = 0;
    for (const auto& city : cities) {
        maxOrder = std::max(maxOrder, city.getVisitOrder());
    }
    
    return maxOrder + 1;
}

/**
 * @brief Prints all cities in a trip in a formatted table
 * @param tripId The ID of the trip to display
 * 
 * Displays a formatted table showing all cities in the specified trip,
 * including their IDs, city IDs, and visit orders. Also shows the total count.
 */
void TripCityService::printTripCities(int tripId) {
    V<TripCity> cities = getCitiesForTrip(tripId);
    
    std::cout << "\n=== Cities in Trip " << tripId << " ===" << std::endl;
    
    if (cities.empty()) {
        std::cout << "No cities found in this trip." << std::endl;
        return;
    }
    
    std::cout << std::setw(5) << "ID" << " | " << std::setw(8) << "City ID" << " | " 
              << std::setw(12) << "Visit Order" << std::endl;
    std::cout << std::string(30, '-') << std::endl;
    
    for (const auto& city : cities) {
        std::cout << std::setw(5) << city.getId() << " | " 
                  << std::setw(8) << city.getCityId() << " | " 
                  << std::setw(12) << city.getVisitOrder() << std::endl;
    }
    
    std::cout << "Total cities: " << cities.size() << std::endl;
}

/**
 * @brief Validates trip-city parameters
 * @param tripId The trip ID to validate
 * @param cityId The city ID to validate
 * @param visitOrder The visit order to validate
 * @return true if all parameters are valid, false otherwise
 * 
 * Performs basic validation on the input parameters:
 * - All IDs must be greater than 0
 * - Visit order must be greater than 0
 * 
 * @note This is a basic validation. Additional business rules may be
 *       implemented in the future.
 */
bool TripCityService::validateTripCity(int tripId, int cityId, int visitOrder) {
    if (tripId <= 0 || cityId <= 0 || visitOrder <= 0) {
        std::cerr << "Error: Invalid parameters (tripId: " << tripId 
                  << ", cityId: " << cityId << ", visitOrder: " << visitOrder << ")" << std::endl;
        return false;
    }
    
    return true;
}




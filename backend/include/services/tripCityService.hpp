#ifndef TRIP_CITY_SERVICE_HPP
#define TRIP_CITY_SERVICE_HPP

#include "../header.hpp"
#include "../repositories/TripCityRepository.hpp"
#include "../entities/TripCity.hpp"
#include <iomanip>

/**
 * @class TripCityService
 * @brief Service layer for TripCity business logic and operations
 * 
 * This class contains the business logic for managing trip-city relationships.
 * It acts as an intermediary between the presentation layer and repository layer,
 * enforcing business rules and providing a clean API for trip-city operations.
 */
class TripCityService {
private:
    TripCityRepository& repo; ///< Reference to the TripCity repository

public:
    /**
     * @brief Constructor
     * @param repository Reference to the TripCity repository
     */
    TripCityService(TripCityRepository& repository);
    
    // Core operations
    /**
     * @brief Add a city to a trip with business logic validation
     * @param tripId The ID of the trip
     * @param cityId The ID of the city to add
     * @param visitOrder The order of visit (optional, auto-assigned if -1)
     * @return true if successful, false otherwise
     * @note Automatically assigns visit order if not provided
     * @note Validates parameters and checks for duplicates
     */
    bool addCityToTrip(int tripId, int cityId, int visitOrder = -1);
    
    /**
     * @brief Get all cities for a specific trip
     * @param tripId The ID of the trip
     * @return Vector of TripCity objects for the trip
     */
    V<TripCity> getCitiesForTrip(int tripId);
    
    /**
     * @brief Remove a city from a trip
     * @param tripId The ID of the trip
     * @param cityId The ID of the city to remove
     * @return true if successful, false otherwise
     */
    bool removeCityFromTrip(int tripId, int cityId);
    
    /**
     * @brief Update the visit order of a city in a trip
     * @param tripId The ID of the trip
     * @param cityId The ID of the city
     * @param newOrder The new visit order
     * @return true if successful, false otherwise
     */
    bool updateVisitOrder(int tripId, int cityId, int newOrder);
    
    // Utility operations
    /**
     * @brief Check if a city already exists in a trip
     * @param tripId The ID of the trip
     * @param cityId The ID of the city
     * @return true if city exists in trip, false otherwise
     */
    bool cityExistsInTrip(int tripId, int cityId);
    
    /**
     * @brief Get the next available visit order for a trip
     * @param tripId The ID of the trip
     * @return The next visit order number
     * @note Returns 1 if no cities exist in the trip
     */
    int getNextVisitOrder(int tripId);
    
    /**
     * @brief Display all cities in a trip in a formatted table
     * @param tripId The ID of the trip
     * @note Prints to console in a formatted table
     */
    void printTripCities(int tripId);
    
    // Validation
    /**
     * @brief Validate TripCity parameters
     * @param tripId The trip ID to validate
     * @param cityId The city ID to validate
     * @param visitOrder The visit order to validate
     * @return true if all parameters are valid, false otherwise
     * @note Valid parameters must be positive integers
     */
    bool validateTripCity(int tripId, int cityId, int visitOrder);
};

#endif

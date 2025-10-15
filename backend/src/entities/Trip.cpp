
/**
 * @file Trip.cpp
 * @brief Implementation of Trip entity class
 */

#include "../../include/entities/Trip.hpp"

// ============================================================================
// CONSTRUCTORS
// ============================================================================

/**
 * @brief Default constructor implementation
 * 
 * Creates an empty Trip object with default values.
 */
Trip::Trip() {}

/**
 * @brief Full constructor implementation
 * @param id The unique identifier for the trip
 * @param start_city_id The ID of the starting city
 * @param trip_type The type of the trip
 * @param total_distance The total distance of the trip
 * 
 * Creates a Trip object with all specified values.
 */
Trip::Trip(int id, int start_city_id, std::string trip_type, double total_distance) :
    id(id), start_city_id(start_city_id), trip_type(trip_type),
     total_distance(total_distance) {}

/**
 * @brief Constructor for new trips implementation
 * @param start_city_id The ID of the starting city
 * @param trip_type The type of the trip
 * @param total_distance The total distance of the trip
 * 
 * Creates a Trip object for new trips where ID will be auto-generated.
 */
Trip::Trip(int start_city_id, std::string trip_type, double total_distance) :
    start_city_id(start_city_id), trip_type(trip_type),
     total_distance(total_distance) {}

// ============================================================================
// GETTERS
// ============================================================================

/**
 * @brief Get the trip ID
 * @return The unique identifier for the trip
 */
int Trip::getId() const
    {
        return id;
    }

/**
 * @brief Get the starting city ID
 * @return The ID of the starting city
 */
int Trip::getStartCityId() const
    {
        return start_city_id;
    }

/**
 * @brief Get the trip type
 * @return The type of the trip
 */
std::string Trip::getTripType() const
    {
        return trip_type;
    }

/**
 * @brief Get the total distance
 * @return The total distance of the trip in kilometers
 */
double Trip::getTotalDistance() const
    {
        return total_distance;
    }

// ============================================================================
// SETTERS
// ============================================================================

/**
 * @brief Set the trip ID
 * @param id The new trip ID
 */
void Trip::setId(int id)
    {
        this->id = id;
    }

/**
 * @brief Set the starting city ID
 * @param start_city_id The new starting city ID
 */
void Trip::setStartCityId(int start_city_id)
    {
        this->start_city_id = start_city_id;
    }

/**
 * @brief Set the trip type
 * @param trip_type The new trip type
 */
void Trip::setTripType(std::string trip_type)
    {
        this->trip_type = trip_type;
    }

/**
 * @brief Set the total distance
 * @param total_distance The new total distance
 */
void Trip::setTotalDistance(double total_distance)
    {
        this->total_distance = total_distance;
    }

// ============================================================================
// VALIDATION
// ============================================================================

/**
 * @brief Validate if the trip has valid data
 * @return True if the trip is valid, false otherwise
 * 
 * Checks if all required fields have valid values:
 * - ID must be greater than 0
 * - Starting city ID must be greater than 0
 * - Total distance must be greater than 0
 */
bool Trip::isValid() const
    {
        return (id > 0 && start_city_id > 0 && total_distance > 0);
    }

// ============================================================================
// TRIP PLANNING METHODS (PLACEHOLDER IMPLEMENTATIONS)
// ============================================================================

/**
 * @brief Check if a city is included in this trip
 * @param cityId The city ID to check
 * @return True if city is in the trip, false otherwise
 * 
 * @note This is a placeholder implementation.
 * In a real implementation, this would query the trip_cities table
 * to check if the city is already part of this trip.
 */
bool Trip::hasCity(int cityId) const {
    // This should check if the city is already in the trip_cities table
    // For now, we'll implement a simple version
    // In a real implementation, this would query the trip_cities table
    return false; // Placeholder - needs proper implementation
}

/**
 * @brief Get the number of cities in this trip
 * @return The number of cities in the trip
 * 
 * @note This is a placeholder implementation.
 * In a real implementation, this would count entries in trip_cities table
 * to determine the actual number of cities in the trip.
 */
int Trip::getTripSize() const {
    // This should return the number of cities in the trip
    // For now, we'll return a placeholder
    // In a real implementation, this would count entries in trip_cities table
    return 0; // Placeholder - needs proper implementation
}

/**
 * @brief Add a city to the trip
 * @param trip Reference to the trip to modify
 * @param cityId ID of the city to add
 * 
 * @note This is a placeholder implementation.
 * This method should probably be moved to TripCityService
 * and would create a TripCity relationship in the database.
 */
void Trip::addTC(Trip& trip, int cityId) {
    // This should add a city to the trip_cities table
    // This method should probably be moved to TripCityService
    // For now, it's a placeholder
}


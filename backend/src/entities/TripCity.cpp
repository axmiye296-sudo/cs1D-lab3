/**
 * @file tripCities.cpp
 * @brief Implementation of TripCity entity class
 * @author CS1D Lab 3 Team
 * @date 2025
 * 
 * This file contains the implementation of the TripCity entity class,
 * which represents the relationship between trips and cities with visit order.
 */

#include "../../include/entities/TripCity.hpp"

// ============================================================================
// CONSTRUCTORS
// ============================================================================

/**
 * @brief Default constructor
 * 
 * Creates a TripCity object with all fields initialized to 0.
 * This is typically used when creating a new entity before setting values.
 */
TripCity::TripCity() : id(0), tripId(0), cityId(0), visitOrder(0) {}

/**
 * @brief Full constructor with all parameters
 * @param id The unique identifier in the database
 * @param tripId The ID of the trip
 * @param cityId The ID of the city
 * @param visitOrder The order of visit in the trip
 * 
 * Creates a TripCity object with all fields specified.
 * This is typically used when loading data from the database.
 */
TripCity::TripCity(int id, int tripId, int cityId, int visitOrder) 
    : id(id), tripId(tripId), cityId(cityId), visitOrder(visitOrder) {}

/**
 * @brief Constructor for new entities (without ID)
 * @param tripId The ID of the trip
 * @param cityId The ID of the city
 * @param visitOrder The order of visit in the trip
 * 
 * Creates a TripCity object for new entities that don't have a database ID yet.
 * The ID is set to 0, indicating this is a new record.
 */
TripCity::TripCity(int tripId, int cityId, int visitOrder) 
    : id(0), tripId(tripId), cityId(cityId), visitOrder(visitOrder) {}

// ============================================================================
// GETTERS
// ============================================================================

/**
 * @brief Gets the unique identifier
 * @return int The database ID of this TripCity record
 */
int TripCity::getId() const { return id; }

/**
 * @brief Gets the trip ID
 * @return int The ID of the associated trip
 */
int TripCity::getTripId() const { return tripId; }

/**
 * @brief Gets the city ID
 * @return int The ID of the associated city
 */
int TripCity::getCityId() const { return cityId; }

/**
 * @brief Gets the visit order
 * @return int The order of visit in the trip
 */
int TripCity::getVisitOrder() const { return visitOrder; }

// ============================================================================
// SETTERS
// ============================================================================

/**
 * @brief Sets the unique identifier
 * @param id The database ID to set
 * 
 * @note This should typically only be called by the repository layer
 *       when loading data from the database.
 */
void TripCity::setId(int id) { this->id = id; }

/**
 * @brief Sets the trip ID
 * @param tripId The ID of the trip to associate with
 */
void TripCity::setTripId(int tripId) { this->tripId = tripId; }

/**
 * @brief Sets the city ID
 * @param cityId The ID of the city to associate with
 */
void TripCity::setCityId(int cityId) { this->cityId = cityId; }

/**
 * @brief Sets the visit order
 * @param visitOrder The order of visit in the trip
 * 
 * @note Visit order should be unique within a trip and typically
 *       starts from 1 and increments sequentially.
 */
void TripCity::setVisitOrder(int visitOrder) { this->visitOrder = visitOrder; }

// ============================================================================
// VALIDATION
// ============================================================================

/**
 * @brief Validates the TripCity object
 * @return true if the object is valid, false otherwise
 * 
 * Performs basic validation on the TripCity object:
 * - Trip ID must be greater than 0
 * - City ID must be greater than 0
 * - Visit order must be greater than 0
 * 
 * @note This is basic validation. Additional business rules may
 *       be enforced at the service layer.
 */
bool TripCity::isValid() const {
    return tripId > 0 && cityId > 0 && visitOrder > 0;
}

// ============================================================================
// UTILITY METHODS
// ============================================================================

/**
 * @brief Converts the TripCity object to a string representation
 * @return std::string String representation of the object
 * 
 * Creates a human-readable string representation of the TripCity object,
 * useful for debugging and logging purposes.
 * 
 * Format: "TripCity{id=X, tripId=Y, cityId=Z, visitOrder=W}"
 */
std::string TripCity::toString() const {
    return "TripCity{id=" + std::to_string(id) +
           ", tripId=" + std::to_string(tripId) +
           ", cityId=" + std::to_string(cityId) +
           ", visitOrder=" + std::to_string(visitOrder) + "}";
}

/**
 * @brief Compares this TripCity with another for equality
 * @param other The TripCity object to compare with
 * @return true if both objects are equal, false otherwise
 * 
 * Performs deep comparison of all fields in the TripCity object.
 * Two TripCity objects are considered equal if all their fields match.
 */
bool TripCity::equals(const TripCity& other) const {
    return id == other.id && tripId == other.tripId &&
           cityId == other.cityId && visitOrder == other.visitOrder;
}
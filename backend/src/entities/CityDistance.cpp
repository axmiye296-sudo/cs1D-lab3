/**
 * @file CityDistance.cpp
 * @brief Implementation of CityDistance entity class
 */

#include "../../include/entities/CityDistance.hpp"

// ============================================================================
// CONSTRUCTORS
// ============================================================================

/**
 * @brief Default constructor implementation
 * 
 * Creates an empty CityDistance object with:
 * - From City ID: 0
 * - To City ID: 0
 * - Distance: 0
 */
CityDistance::CityDistance() : fromCityId(0), toCityId(0), distance(0) {}

/**
 * @brief Parameterized constructor implementation
 * @param fromCityId ID of the source city
 * @param toCityId ID of the destination city
 * @param distance Distance between the cities in kilometers
 * 
 * Creates a CityDistance object with the specified values.
 */
CityDistance::CityDistance(int fromCityId, int toCityId, int distance)
    : fromCityId(fromCityId), toCityId(toCityId), distance(distance) {}

// ============================================================================
// GETTERS
// ============================================================================

/**
 * @brief Get the source city ID
 * @return The ID of the source city
 */
int CityDistance::getFromCityId() const { return fromCityId; }

/**
 * @brief Get the destination city ID
 * @return The ID of the destination city
 */
int CityDistance::getToCityId() const { return toCityId; }

/**
 * @brief Get the distance between cities
 * @return The distance in kilometers
 */
int CityDistance::getDistance() const { return distance; }

// ============================================================================
// SETTERS
// ============================================================================

/**
 * @brief Set the source city ID
 * @param fromCityId The new source city ID
 */
void CityDistance::setFromCityId(int fromCityId) { this->fromCityId = fromCityId; }

/**
 * @brief Set the destination city ID
 * @param toCityId The new destination city ID
 */
void CityDistance::setToCityId(int toCityId) { this->toCityId = toCityId; }

/**
 * @brief Set the distance between cities
 * @param distance The new distance in kilometers
 */
void CityDistance::setDistance(int distance) { this->distance = distance; }




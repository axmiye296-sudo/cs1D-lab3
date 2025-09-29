/**
 * @file cityDistances.cpp
 * @brief Implementation of CityDistance entity class
 * @author CS1D Lab 3 Team
 * @date 2025
 *
 * This file contains the implementation of the CityDistance entity class,
 * which represents the directed distance from one city to another.
 * In the database, the primary key is the composite (from_city_id, to_city_id).
 */

#include "../../include/entities/CityDistance.hpp"
#include <string>

// ============================================================================
// CONSTRUCTORS
// ============================================================================

/**
 * @brief Default constructor
 *
 * Creates a CityDistance object with all fields initialized to 0.
 * This is typically used when creating a new entity before setting values.
 */
CityDistance::CityDistance()
    : fromCityId(0), toCityId(0), distance(0) {}

/**
 * @brief Full constructor with all parameters
 * @param fromCityId The ID of the origin city
 * @param toCityId   The ID of the destination city
 * @param distanceKm The distance in kilometers from origin to destination
 *
 * Creates a CityDistance object with all fields specified.
 * This is typically used when loading data from the database.
 */
CityDistance::CityDistance(int f, int t, int d): fromCityId(f), toCityId(t), distance(d) {}

// ============================================================================
// GETTERS
// ============================================================================

/**
 * @brief Gets the origin (from) city ID
 * @return int The ID of the origin city
 */
int CityDistance::getFromCityId() const { return fromCityId; }

/**
 * @brief Gets the destination (to) city ID
 * @return int The ID of the destination city
 */
int CityDistance::getToCityId() const { return toCityId; }

/**
 * @brief Gets the distance in kilometers
 * @return double The distance in km
 */
int CityDistance::getDistance() const { return distance; }

// ============================================================================
// SETTERS
// ============================================================================

/**
 * @brief Sets the distance in kilometers
 * @param d The distance in km (must be >= 0)
 */
void CityDistance::setDistance(int d) { distance = d; }

// ============================================================================
// VALIDATION
// ============================================================================

/**
 * @brief Validates the CityDistance object
 * @return true if the object is valid, false otherwise
 *
 * Performs basic validation on the CityDistance object:
 * - fromCityId must be greater than 0
 * - toCityId must be greater than 0
 * - fromCityId must not equal toCityId
 * - distanceKm must be >= 0
 *
 * @note This is basic validation. Additional business rules (such as
 *       symmetry constraints) may be enforced at the service/repository layer.
 */
bool CityDistance::isValid() const {
    return fromCityId > 0
        && toCityId > 0
        && fromCityId != toCityId
        && distance >= 0;
}

// ============================================================================
// UTILITY METHODS
// ============================================================================

/**
 * @brief Converts the CityDistance object to a string representation
 * @return std::string String representation of the object
 *
 * Format: "CityDistance{fromCityId=X, toCityId=Y, distanceKm=Z.ZZ}"
 */
std::string CityDistance::toString() const {
    return "CityDistance{fromCityId=" + std::to_string(fromCityId) +
           ", toCityId=" + std::to_string(toCityId) +
           ", distanceKm=" + std::to_string(distance) + "}";
}

/**
 * @brief Compares this CityDistance with another for equality
 * @param other The CityDistance object to compare with
 * @return true if both objects are equal, false otherwise
 *
 * Two CityDistance objects are considered equal if:
 * - fromCityId matches
 * - toCityId matches
 * - distanceKm matches exactly
 *
 * @note If you want fuzzy comparison for doubles, adapt this to use an epsilon.
 */
bool CityDistance::equals(const CityDistance& other) const {
    return fromCityId == other.fromCityId
        && toCityId   == other.toCityId
        && distance == other.distance;
}


/**
 * @file CityDistanceRepository.cpp
 * @brief Implementation of CityDistanceRepository class
 */

#include "../../include/repositories/CityDistanceRepository.hpp"
#include "../../include/databaseManager.hpp"
#include <iostream>

// ============================================================================
// CONSTRUCTOR
// ============================================================================

/**
 * @brief Constructor implementation
 * @param db Reference to DatabaseManager instance
 * 
 * Initializes the repository with a database connection.
 * The database reference is stored for later use in SQL operations.
 */
CityDistanceRepository::CityDistanceRepository(DatabaseManager& db) : database(db) {}

// ============================================================================
// PUBLIC METHODS
// ============================================================================

/**
 * @brief Find distances from a specific city
 * @param fromCityId The ID of the source city
 * @return Vector containing CityDistance objects from the specified city
 * 
 * Retrieves all distance records where the specified city is the source.
 * Results are ordered by distance (ascending) for optimal trip planning.
 */
V<CityDistance> CityDistanceRepository::findByFromCity(int fromCityId) {
    V<CityDistance> result;
    
    std::string query = "SELECT from_city_id, to_city_id, distance FROM city_distances WHERE from_city_id = " + 
                       std::to_string(fromCityId) + " ORDER BY distance ASC;";
    
    std::cout << "🔍 Executing query: " << query << std::endl;
    
    auto dbResult = database.executeSelect(query);
    
    for (const auto& row : dbResult) {
        if (row.size() >= 3) {
            result.push_back(mapRowToEntity(row));
        }
    }
    
    std::cout << "✅ Found " << result.size() << " distances from city " << fromCityId << std::endl;
    return result;
}

/**
 * @brief Get distance between two specific cities
 * @param fromCityId The ID of the source city
 * @param toCityId The ID of the destination city
 * @return The distance between the cities, or -1 if not found
 * 
 * Retrieves the distance between two specific cities.
 * Returns -1 if no distance record exists between the cities.
 */
int CityDistanceRepository::getDistance(int fromCityId, int toCityId) {
    std::string query = "SELECT distance FROM city_distances WHERE from_city_id = " + 
                       std::to_string(fromCityId) + " AND to_city_id = " + std::to_string(toCityId) + ";";
    
    auto dbResult = database.executeSelect(query);
    
    if (!dbResult.empty() && !dbResult[0].empty()) {
        int distance = std::stoi(dbResult[0][0]);
        std::cout << "📏 Distance from " << fromCityId << " to " << toCityId << ": " << distance << " km" << std::endl;
        return distance;
    }
    
    std::cout << "❌ No distance found from " << fromCityId << " to " << toCityId << std::endl;
    return -1; // Distance not found
}

/**
 * @brief Get all city distances from the database
 * @return Vector containing all CityDistance objects
 * 
 * Retrieves all distance records from the database.
 * Results are ordered by source city ID and distance for consistent ordering.
 */
V<CityDistance> CityDistanceRepository::findAll() {
    V<CityDistance> result;
    
    std::string query = "SELECT from_city_id, to_city_id, distance FROM city_distances ORDER BY from_city_id, distance;";
    
    auto dbResult = database.executeSelect(query);
    
    for (const auto& row : dbResult) {
        if (row.size() >= 3) {
            result.push_back(mapRowToEntity(row));
        }
    }
    
    return result;
}

// ============================================================================
// ADMIN METHODS
// ============================================================================

/**
 * @brief Save a city distance record
 * @param cityDistance The CityDistance object to save
 * @return True if save successful, false otherwise
 * 
 * Saves a new city distance record to the database.
 * If a distance already exists between the same cities, it updates the existing record.
 * Used for adding new distance relationships between cities.
 */
bool CityDistanceRepository::save(const CityDistance& cityDistance) {
    // Check if distance already exists
    int existingDistance = getDistance(cityDistance.getFromCityId(), cityDistance.getToCityId());
    
    if (existingDistance != -1) {
        // Update existing distance
        std::string updateQuery = "UPDATE city_distances SET distance = " + 
                                std::to_string(cityDistance.getDistance()) + 
                                " WHERE from_city_id = " + std::to_string(cityDistance.getFromCityId()) + 
                                " AND to_city_id = " + std::to_string(cityDistance.getToCityId()) + ";";
        
        std::cout << "🔄 Updating existing distance: " << updateQuery << std::endl;
        return database.executeInsert(updateQuery);
    } else {
        // Insert new distance
        std::string insertQuery = "INSERT INTO city_distances (from_city_id, to_city_id, distance) VALUES (" +
                                std::to_string(cityDistance.getFromCityId()) + ", " +
                                std::to_string(cityDistance.getToCityId()) + ", " +
                                std::to_string(cityDistance.getDistance()) + ");";
        
        std::cout << "➕ Inserting new distance: " << insertQuery << std::endl;
        return database.executeInsert(insertQuery);
    }
}

// ============================================================================
// PRIVATE HELPER METHODS
// ============================================================================

/**
 * @brief Convert database row to CityDistance object
 * @param row Vector of strings representing a database row
 * @return CityDistance object created from the row data
 * 
 * Maps a database row (vector of strings) to a CityDistance object.
 * This is a helper method used internally by other repository methods.
 */
CityDistance CityDistanceRepository::mapRowToEntity(const std::vector<std::string>& row) {
    int fromCityId = std::stoi(row[0]);
    int toCityId = std::stoi(row[1]);
    int distance = std::stoi(row[2]);
    
    return CityDistance(fromCityId, toCityId, distance);
}




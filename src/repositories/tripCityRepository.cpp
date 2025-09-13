/**
 * @file tripCityRepository.cpp
 * @brief Implementation of TripCityRepository class for database operations
 * @author CS1D Lab 3 Team
 * @date 2024
 * 
 * This file contains the data access layer implementation for managing
 * trip-city relationships in the SQLite database. It handles all CRUD
 * operations and query building for the trip_cities table.
 */

#include "../include/repositories/TripCityRepository.hpp"
#include <iostream>

/**
 * @brief Constructor for TripCityRepository
 * @param database Reference to DatabaseManager for SQLite operations
 * 
 * Initializes the repository with a database manager instance.
 * All database operations will be performed through this manager.
 */
TripCityRepository::TripCityRepository(DatabaseManager& database) : db(database) {}

/**
 * @brief Saves a TripCity entity to the database
 * @param tripCity Reference to TripCity object to save
 * @return true if save operation was successful, false otherwise
 * 
 * Determines whether to insert a new record or update an existing one
 * based on the entity's ID. If ID is 0, performs INSERT; otherwise UPDATE.
 * 
 * @note The tripCity parameter is modified during the save process
 *       to reflect the actual database state.
 */
bool TripCityRepository::save(TripCity& tripCity) {
    std::string query;
    if (tripCity.getId() == 0) {
        // Insert new
        query = buildInsertQuery(tripCity);
    } else {
        // Update existing
        query = buildUpdateQuery(tripCity);
    }
    
    return db.executeQuery(query);
}

/**
 * @brief Finds all cities for a specific trip
 * @param tripId The ID of the trip to search for
 * @return V<TripCity> Vector of TripCity objects for the trip
 * 
 * Retrieves all cities associated with the given trip ID,
 * ordered by visit order. Returns an empty vector if no cities found.
 */
V<TripCity> TripCityRepository::findByTrip(int tripId) {
    V<TripCity> result;
    std::string query = buildSelectByTripQuery(tripId);
    auto dbResult = db.executeSelect(query);
    
    if (!dbResult.empty()) {
        for (const auto& row : dbResult) {
            if (row.size() >= 4) {
                TripCity tripCity = mapRowToEntity(row);
                result.push_back(tripCity);
            }
        }
    }
    
    return result;
}

/**
 * @brief Removes a TripCity record by ID
 * @param id The ID of the record to delete
 * @return true if deletion was successful, false otherwise
 * 
 * Performs a hard delete of the specified TripCity record from the database.
 */
bool TripCityRepository::remove(int id) {
    std::string query = buildDeleteQuery(id);
    return db.executeQuery(query);
}

/**
 * @brief Retrieves all TripCity records from the database
 * @return V<TripCity> Vector of all TripCity objects
 * 
 * Fetches all trip-city relationships from the database,
 * ordered by trip ID and visit order.
 */
V<TripCity> TripCityRepository::findAll() {
    V<TripCity> result;
    std::string query = buildSelectAllQuery();
    auto dbResult = db.executeSelect(query);
    
    if (!dbResult.empty()) {
        for (const auto& row : dbResult) {
            if (row.size() >= 4) {
                TripCity tripCity = mapRowToEntity(row);
                result.push_back(tripCity);
            }
        }
    }
    
    return result;
}

/**
 * @brief Loads a specific TripCity record by ID
 * @param id The ID of the record to load
 * @param tripCity Reference to TripCity object to populate
 * @return true if record was found and loaded, false otherwise
 * 
 * Loads a specific TripCity record into the provided object.
 * The object is only modified if a matching record is found.
 */
bool TripCityRepository::load(int id, TripCity& tripCity) {
    std::string query = buildSelectQuery(id);
    auto dbResult = db.executeSelect(query);
    
    if (!dbResult.empty() && dbResult[0].size() >= 4) {
        tripCity = mapRowToEntity(dbResult[0]);
        return true;
    }
    
    return false;
}

/**
 * @brief Finds all trips that include a specific city
 * @param cityId The ID of the city to search for
 * @return V<TripCity> Vector of TripCity objects for the city
 * 
 * Retrieves all trip relationships for the given city ID,
 * ordered by visit order within each trip.
 */
V<TripCity> TripCityRepository::findByCity(int cityId) {
    V<TripCity> result;
    std::string query = "SELECT id, trip_id, city_id, visit_order FROM trip_cities WHERE city_id = " + 
                       std::to_string(cityId) + " ORDER BY visit_order;";
    auto dbResult = db.executeSelect(query);
    
    if (!dbResult.empty()) {
        for (const auto& row : dbResult) {
            if (row.size() >= 4) {
                TripCity tripCity = mapRowToEntity(row);
                result.push_back(tripCity);
            }
        }
    }
    
    return result;
}

/**
 * @brief Checks if a visit order already exists for a trip
 * @param tripId The ID of the trip
 * @param visitOrder The visit order to check
 * @return true if visit order exists, false otherwise
 * 
 * Used to prevent duplicate visit orders within the same trip.
 * This is important for maintaining proper city sequence.
 */
bool TripCityRepository::existsByTripAndOrder(int tripId, int visitOrder) {
    std::string query = "SELECT COUNT(*) FROM trip_cities WHERE trip_id = " + std::to_string(tripId) + 
                       " AND visit_order = " + std::to_string(visitOrder) + ";";
    auto dbResult = db.executeSelect(query);
    
    if (!dbResult.empty() && !dbResult[0].empty()) {
        int count = std::stoi(dbResult[0][0]);
        return count > 0;
    }
    
    return false;
}

/**
 * @brief Saves multiple TripCity records in a batch
 * @param tripCities Vector of TripCity objects to save
 * @return true if all saves were successful, false if any failed
 * 
 * Performs batch save operation. If any individual save fails,
 * the entire operation is considered failed.
 * 
 * @note This is not a transactional operation - partial saves may occur
 *       if the operation fails partway through.
 */
bool TripCityRepository::saveAll(const V<TripCity>& tripCities) {
    for (const auto& tripCity : tripCities) {
        TripCity temp = tripCity; // Create non-const copy
        if (!save(temp)) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Removes all cities from a specific trip
 * @param tripId The ID of the trip to clear
 * @return true if removal was successful, false otherwise
 * 
 * Deletes all trip-city relationships for the specified trip.
 * This effectively removes all cities from the trip.
 */
bool TripCityRepository::removeByTrip(int tripId) {
    std::string query = "DELETE FROM trip_cities WHERE trip_id = " + std::to_string(tripId) + ";";
    return db.executeQuery(query);
}

// ============================================================================
// HELPER METHODS
// ============================================================================

/**
 * @brief Maps a database row to a TripCity entity
 * @param row Vector of strings representing a database row
 * @return TripCity object created from the row data
 * 
 * Converts raw database row data into a TripCity object.
 * Expects row format: [id, trip_id, city_id, visit_order]
 * 
 * @warning Assumes row has at least 4 elements. No bounds checking performed.
 */
TripCity TripCityRepository::mapRowToEntity(const std::vector<std::string>& row) {
    int id = std::stoi(row[0]);
    int tripId = std::stoi(row[1]);
    int cityId = std::stoi(row[2]);
    int visitOrder = std::stoi(row[3]);
    
    return TripCity(id, tripId, cityId, visitOrder);
}

/**
 * @brief Builds an INSERT SQL query for a TripCity
 * @param tripCity The TripCity object to create query for
 * @return std::string The complete INSERT SQL query
 * 
 * Generates a parameterized INSERT statement for adding a new
 * trip-city relationship to the database.
 */
std::string TripCityRepository::buildInsertQuery(const TripCity& tripCity) {
    return "INSERT INTO trip_cities (trip_id, city_id, visit_order) VALUES (" +
           std::to_string(tripCity.getTripId()) + ", " +
           std::to_string(tripCity.getCityId()) + ", " +
           std::to_string(tripCity.getVisitOrder()) + ");";
}

/**
 * @brief Builds an UPDATE SQL query for a TripCity
 * @param tripCity The TripCity object to create query for
 * @return std::string The complete UPDATE SQL query
 * 
 * Generates a parameterized UPDATE statement for modifying an
 * existing trip-city relationship in the database.
 */
std::string TripCityRepository::buildUpdateQuery(const TripCity& tripCity) {
    return "UPDATE trip_cities SET trip_id = " + std::to_string(tripCity.getTripId()) +
           ", city_id = " + std::to_string(tripCity.getCityId()) +
           ", visit_order = " + std::to_string(tripCity.getVisitOrder()) +
           " WHERE id = " + std::to_string(tripCity.getId()) + ";";
}

/**
 * @brief Builds a DELETE SQL query by ID
 * @param id The ID of the record to delete
 * @return std::string The complete DELETE SQL query
 * 
 * Generates a DELETE statement for removing a specific
 * trip-city relationship by its unique ID.
 */
std::string TripCityRepository::buildDeleteQuery(int id) {
    return "DELETE FROM trip_cities WHERE id = " + std::to_string(id) + ";";
}

/**
 * @brief Builds a SELECT SQL query by ID
 * @param id The ID of the record to select
 * @return std::string The complete SELECT SQL query
 * 
 * Generates a SELECT statement for retrieving a specific
 * trip-city relationship by its unique ID.
 */
std::string TripCityRepository::buildSelectQuery(int id) {
    return "SELECT id, trip_id, city_id, visit_order FROM trip_cities WHERE id = " + std::to_string(id) + ";";
}

/**
 * @brief Builds a SELECT ALL SQL query
 * @return std::string The complete SELECT ALL SQL query
 * 
 * Generates a SELECT statement for retrieving all
 * trip-city relationships, ordered by trip ID and visit order.
 */
std::string TripCityRepository::buildSelectAllQuery() {
    return "SELECT id, trip_id, city_id, visit_order FROM trip_cities ORDER BY trip_id, visit_order;";
}

/**
 * @brief Builds a SELECT SQL query by trip ID
 * @param tripId The ID of the trip to select cities for
 * @return std::string The complete SELECT SQL query
 * 
 * Generates a SELECT statement for retrieving all cities
 * associated with a specific trip, ordered by visit order.
 */
std::string TripCityRepository::buildSelectByTripQuery(int tripId) {
    return "SELECT id, trip_id, city_id, visit_order FROM trip_cities WHERE trip_id = " + 
           std::to_string(tripId) + " ORDER BY visit_order;";
}





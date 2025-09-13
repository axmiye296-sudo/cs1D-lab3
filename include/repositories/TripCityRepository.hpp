#ifndef TRIP_CITY_REPOSITORY_HPP
#define TRIP_CITY_REPOSITORY_HPP

#include "../header.hpp"
#include "../databaseManager.hpp"
#include "../entities/tripCities.hpp"

/**
 * @class TripCityRepository
 * @brief Repository pattern implementation for TripCity data access
 * 
 * This class handles all database operations for TripCity entities,
 * providing a clean interface between the service layer and database layer.
 * Implements the Repository pattern for better separation of concerns.
 */
class TripCityRepository {
private:
    DatabaseManager& db; ///< Reference to the database manager

public:
    /**
     * @brief Constructor
     * @param database Reference to the database manager
     */
    TripCityRepository(DatabaseManager& database);
    
    // CRUD operations
    /**
     * @brief Save a TripCity entity to the database
     * @param tripCity The TripCity object to save
     * @return true if successful, false otherwise
     * @note If ID is 0, performs INSERT; otherwise performs UPDATE
     */
    bool save(TripCity& tripCity);
    
    /**
     * @brief Load a TripCity entity from the database by ID
     * @param id The database ID to load
     * @param tripCity Reference to TripCity object to populate
     * @return true if found and loaded, false otherwise
     */
    bool load(int id, TripCity& tripCity);
    
    /**
     * @brief Remove a TripCity entity from the database
     * @param id The database ID to remove
     * @return true if successful, false otherwise
     */
    bool remove(int id);
    
    /**
     * @brief Get all TripCity entities from the database
     * @return Vector containing all TripCity objects
     */
    V<TripCity> findAll();
    
    // TripCity-specific queries
    /**
     * @brief Find all cities for a specific trip
     * @param tripId The trip ID to search for
     * @return Vector of TripCity objects for the specified trip
     */
    V<TripCity> findByTrip(int tripId);
    
    /**
     * @brief Find all trips that include a specific city
     * @param cityId The city ID to search for
     * @return Vector of TripCity objects for the specified city
     */
    V<TripCity> findByCity(int cityId);
    
    /**
     * @brief Check if a visit order already exists in a trip
     * @param tripId The trip ID
     * @param visitOrder The visit order to check
     * @return true if the visit order exists, false otherwise
     */
    bool existsByTripAndOrder(int tripId, int visitOrder);
    
    // Batch operations
    /**
     * @brief Save multiple TripCity entities at once
     * @param tripCities Vector of TripCity objects to save
     * @return true if all successful, false if any fails
     */
    bool saveAll(const V<TripCity>& tripCities);
    
    /**
     * @brief Remove all cities from a specific trip
     * @param tripId The trip ID to clear
     * @return true if successful, false otherwise
     */
    bool removeByTrip(int tripId);
    
private:
    // Helper methods
    /**
     * @brief Convert database row to TripCity entity
     * @param row Database row as vector of strings
     * @return TripCity object created from the row
     */
    TripCity mapRowToEntity(const std::vector<std::string>& row);
    
    /**
     * @brief Build INSERT SQL query for TripCity
     * @param tripCity The TripCity object to insert
     * @return SQL INSERT query string
     */
    std::string buildInsertQuery(const TripCity& tripCity);
    
    /**
     * @brief Build UPDATE SQL query for TripCity
     * @param tripCity The TripCity object to update
     * @return SQL UPDATE query string
     */
    std::string buildUpdateQuery(const TripCity& tripCity);
    
    /**
     * @brief Build DELETE SQL query for TripCity
     * @param id The ID to delete
     * @return SQL DELETE query string
     */
    std::string buildDeleteQuery(int id);
    
    /**
     * @brief Build SELECT SQL query for TripCity by ID
     * @param id The ID to select
     * @return SQL SELECT query string
     */
    std::string buildSelectQuery(int id);
    
    /**
     * @brief Build SELECT SQL query for all TripCity records
     * @return SQL SELECT query string
     */
    std::string buildSelectAllQuery();
    
    /**
     * @brief Build SELECT SQL query for TripCity by trip ID
     * @param tripId The trip ID to select
     * @return SQL SELECT query string
     */
    std::string buildSelectByTripQuery(int tripId);
};

#endif

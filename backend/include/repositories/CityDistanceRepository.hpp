/**
 * @file CityDistanceRepository.hpp
 * @brief Repository class for CityDistance entity database operations
 */

 #ifndef CITY_DISTANCE_REPOSITORY_HPP
 #define CITY_DISTANCE_REPOSITORY_HPP
 
 #include "../header.hpp"
 #include "../entities/CityDistance.hpp"
 #include "../databaseManager.hpp"
 
 /**
  * @class CityDistanceRepository
  * @brief Handles all database operations for CityDistance entities
  * 
  * The CityDistanceRepository class provides methods to interact with the database
  * for CityDistance entities. It handles distance queries, city-to-city distance
  * lookups, and data mapping between database rows and CityDistance objects.
  */
 class CityDistanceRepository {
 private:
     DatabaseManager& database;  ///< Reference to database connection for SQL queries
 
 public:
     /**
      * @brief Constructor
      * @param db Reference to DatabaseManager instance
      * 
      * Initializes the repository with a database connection.
      */
     CityDistanceRepository(DatabaseManager& db);
     
     /**
      * @brief Find distances from a specific city
      * @param fromCityId The ID of the source city
      * @return Vector containing CityDistance objects from the specified city
      * 
      * Retrieves all distance records where the specified city is the source.
      * This is useful for finding all destinations from a given city.
      */
     V<CityDistance> findByFromCity(int fromCityId);
     
     /**
      * @brief Get distance between two specific cities
      * @param fromCityId The ID of the source city
      * @param toCityId The ID of the destination city
      * @return The distance between the cities, or -1 if not found
      * 
      * Retrieves the distance between two specific cities.
      * Returns -1 if no distance record exists between the cities.
      */
     int getDistance(int fromCityId, int toCityId);
     
     /**
      * @brief Get all city distances from the database
      * @return Vector containing all CityDistance objects
      * 
      * Retrieves all distance records from the database.
      * This is useful for building complete distance matrices.
      */
     V<CityDistance> findAll();
     
     /**
      * @brief Save a city distance record
      * @param cityDistance The CityDistance object to save
      * @return True if save successful, false otherwise
      * 
      * Saves a new city distance record to the database.
      * Used for adding new distance relationships between cities.
      */
     bool save(const CityDistance& cityDistance);
 
 private:
     /**
      * @brief Convert database row to CityDistance object
      * @param row Vector of strings representing a database row
      * @return CityDistance object created from the row data
      * 
      * Maps a database row (vector of strings) to a CityDistance object.
      * This is a helper method used internally by other repository methods.
      */
     CityDistance mapRowToEntity(const std::vector<std::string>& row);
 };
 
 #endif
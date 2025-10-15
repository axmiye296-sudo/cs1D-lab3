/**
 * @file TripRepository.hpp
 * @brief Repository class for Trip entity database operations
 */

 #ifndef TRIP_REPOSITORY_HPP
 #define TRIP_REPOSITORY_HPP
 
 #include "../header.hpp"
 #include "../entities/Trip.hpp"
 
 class DatabaseManager;
 
 /**
  * @class TripRepository
  * @brief Handles all database operations for Trip entities
  * 
  * The TripRepository class provides methods to interact with the database
  * for Trip entities. It handles CRUD operations, trip type filtering,
  * and data mapping between database rows and Trip objects.
  */
 class TripRepository {
 private:
     DatabaseManager& database;  ///< Reference to database connection for SQL queries
 
 public:
     /**
      * @brief Constructor
      * @param database Reference to DatabaseManager instance
      * 
      * Initializes the repository with a database connection.
      */
     TripRepository(DatabaseManager& database);
 
     /**
      * @brief Find trips by trip type
      * @param tripType The type of trip to search for
      * @return Vector containing Trip objects matching the trip type
      * 
      * Retrieves all trips that match the specified trip type.
      * This is useful for finding predefined tour types.
      */
     V<Trip> findByType(const std::string& tripType);
 
     /**
      * @brief Find trips by starting city
      * @param startCityId The ID of the starting city
      * @return Vector containing Trip objects with the specified starting city
      * 
      * Retrieves all trips that start from the specified city.
      * This is useful for custom trip planning.
      */
     V<Trip> findByStartCity(int startCityId);
 
     /**
      * @brief Convert database row to Trip object
      * @param row Vector of strings representing a database row
      * @return Trip object created from the row data
      * 
      * Maps a database row (vector of strings) to a Trip object.
      * This is a helper method used internally by other repository methods.
      */
     Trip mapRowToEntity(const std::vector<std::string>& row);
 
     /**
      * @brief Build INSERT query for Trip
      * @param trip The Trip object to insert
      * @return SQL INSERT query string
      * 
      * Constructs an SQL INSERT statement for the given Trip object.
      * Used internally for database operations.
      */
     std::string buildInsertQuery(const Trip& trip);
 
     /**
      * @brief Build UPDATE query for Trip
      * @param trip The Trip object to update
      * @return SQL UPDATE query string
      * 
      * Constructs an SQL UPDATE statement for the given Trip object.
      * Used internally for database operations.
      */
     std::string buildUpdateQuery(const Trip& trip);
 
     /**
      * @brief Save or update a trip
      * @param trip The Trip object to save
      * @return True if save successful, false otherwise
      * 
      * Saves a new trip or updates an existing one based on the trip's ID.
      * If ID is 0, performs INSERT; otherwise performs UPDATE.
      */
     bool save(Trip& trip);
     
     /**
      * @brief Load a trip by ID
      * @param id The ID of the trip to load
      * @param trip Reference to Trip object to populate
      * @return True if trip found and loaded, false otherwise
      * 
      * Loads a trip from the database by its ID and populates the provided Trip object.
      */
     bool load(int id, Trip& trip);
     
     /**
      * @brief Get all trips from the database
      * @return Vector containing all Trip objects
      * 
      * Retrieves all trips from the database.
      */
     V<Trip> findAll();
 };
 
 #endif
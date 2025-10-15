/**
 * @file databaseManager.hpp
 * @brief Database connection and management class
 */

 #ifndef DATABASE_MANAGER_HPP
 #define DATABASE_MANAGER_HPP
 
 #include <sqlite3.h>
 #include <string>
 #include <vector>
 
 /**
  * @class DatabaseManager
  * @brief Manages SQLite database connections and operations
  * 
  * The DatabaseManager class provides a wrapper around SQLite3 functionality,
  * handling database connections, query execution, and result processing.
  * It serves as the central database access point for the entire application.
  */
 class DatabaseManager {
 private:
     sqlite3* db;        ///< SQLite database connection handle
     std::string dbPath; ///< Path to the SQLite database file
 
 public:
     /**
      * @brief Constructor
      * @param databasePath Path to the SQLite database file
      * 
      * Initializes the database manager with the specified database path.
      * The database connection is established during construction.
      */
     DatabaseManager(const std::string& databasePath);
     
     /**
      * @brief Destructor
      * 
      * Closes the database connection and cleans up resources.
      */
     ~DatabaseManager();
 
     /**
      * @brief Execute a SELECT query and return results
      * @param query The SQL SELECT query to execute
      * @return Vector of vectors containing query results
      * 
      * Executes a SELECT query and returns the results as a vector
      * of rows, where each row is a vector of strings.
      */
     std::vector<std::vector<std::string>> executeQuery(const std::string& query);
     
     /**
      * @brief Execute an INSERT, UPDATE, or DELETE query
      * @param query The SQL query to execute
      * @return True if execution successful, false otherwise
      * 
      * Executes non-SELECT queries (INSERT, UPDATE, DELETE) and
      * returns success status.
      */
     bool executeUpdate(const std::string& query);
     
     /**
      * @brief Check if database connection is valid
      * @return True if connected, false otherwise
      * 
      * Verifies that the database connection is active and functional.
      */
     bool isConnected() const;
     
     /**
      * @brief Get the last error message
      * @return String containing the last SQLite error message
      * 
      * Returns the most recent error message from SQLite operations.
      * Useful for debugging database issues.
      */
     std::string getLastError() const;
 
 private:
     /**
      * @brief Initialize the database connection
      * @return True if connection successful, false otherwise
      * 
      * Establishes connection to the SQLite database file.
      * Called internally during construction.
      */
     bool connect();
     
     /**
      * @brief Close the database connection
      * 
      * Properly closes the SQLite database connection.
      * Called internally during destruction.
      */
     void disconnect();
 };
 
 #endif
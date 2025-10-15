/**
 * @file databaseInterface.hpp
 * @brief Abstract interface for database operations
 */

 #ifndef DATABASE_INTERFACE_HPP
 #define DATABASE_INTERFACE_HPP
 
 #include "header.hpp"
 
 /**
  * @class DatabaseInterface
  * @brief Abstract interface defining common database operations
  * 
  * This interface provides a common contract for different database implementations.
  * It defines the standard operations that any database implementation should support,
  * allowing for easy switching between different database backends.
  */
 class DatabaseInterface {
 public:
     /**
      * @brief Virtual destructor
      * 
      * Ensures proper cleanup of derived classes.
      */
     virtual ~DatabaseInterface() = default;
     
     // Connection management
     /**
      * @brief Establish database connection
      * @return True if connection successful, false otherwise
      * 
      * Initiates a connection to the database system.
      */
     virtual bool connect() = 0;
     
     /**
      * @brief Close database connection
      * 
      * Properly closes the connection to the database.
      */
     virtual void disconnect() = 0;
     
     /**
      * @brief Check if database is connected
      * @return True if connected, false otherwise
      * 
      * Verifies the current connection status.
      */
     virtual bool isConnected() const = 0;
     
     // Generic query execution
     /**
      * @brief Execute a generic query
      * @param query The SQL query to execute
      * @return True if execution successful, false otherwise
      * 
      * Executes any SQL query and returns success status.
      */
     virtual bool executeQuery(const std::string& query) = 0;
     
     /**
      * @brief Execute a SELECT query
      * @param query The SELECT query to execute
      * @return Vector of vectors containing query results
      * 
      * Executes a SELECT query and returns the results as a vector of rows.
      */
     virtual V<std::vector<std::string>> executeSelect(const std::string& query) = 0;
     
     /**
      * @brief Execute an INSERT query
      * @param query The INSERT query to execute
      * @return The ID of the inserted record, or -1 if failed
      * 
      * Executes an INSERT query and returns the ID of the new record.
      */
     virtual int executeInsert(const std::string& query) = 0;
     
     /**
      * @brief Execute an UPDATE query
      * @param query The UPDATE query to execute
      * @return True if execution successful, false otherwise
      * 
      * Executes an UPDATE query and returns success status.
      */
     virtual bool executeUpdate(const std::string& query) = 0;
     
     /**
      * @brief Execute a DELETE query
      * @param query The DELETE query to execute
      * @return True if execution successful, false otherwise
      * 
      * Executes a DELETE query and returns success status.
      */
     virtual bool executeDelete(const std::string& query) = 0;
     
     // Transaction management
     /**
      * @brief Begin a database transaction
      * @return True if transaction started successfully, false otherwise
      * 
      * Starts a new database transaction for atomic operations.
      */
     virtual bool beginTransaction() = 0;
     
     /**
      * @brief Commit the current transaction
      * @return True if commit successful, false otherwise
      * 
      * Commits all changes made during the current transaction.
      */
     virtual bool commitTransaction() = 0;
     
     /**
      * @brief Rollback the current transaction
      * @return True if rollback successful, false otherwise
      * 
      * Undoes all changes made during the current transaction.
      */
     virtual bool rollbackTransaction() = 0;
 };
 
 #endif
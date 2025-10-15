/**
 * @file databaseManager.hpp
 * @brief Database connection and management class using singleton pattern
 */

#ifndef DATABASE_MANAGER_HPP
#define DATABASE_MANAGER_HPP

#include <sqlite3.h>
#include <string>
#include <vector>
#include <memory>

/**
 * @class DatabaseManager
 * @brief Manages SQLite database connections and operations using singleton pattern
 * 
 * The DatabaseManager class provides a wrapper around SQLite3 functionality,
 * handling database connections, query execution, and result processing.
 * It uses the singleton pattern to ensure only one database connection exists.
 */
class DatabaseManager {
private:
    sqlite3* db;                    ///< SQLite database connection handle
    std::string dbPath;             ///< Path to the SQLite database file
    bool isConnected_;              ///< Connection status flag
    bool inTransaction;             ///< Transaction status flag
    static std::unique_ptr<DatabaseManager> instance; ///< Singleton instance

    /**
     * @brief Private constructor for singleton pattern
     * 
     * Initializes the database manager with default settings.
     * The database connection is established when connect() is called.
     */
    DatabaseManager();

public:
    /**
     * @brief Destructor
     * 
     * Closes the database connection and cleans up resources.
     */
    ~DatabaseManager();

    /**
     * @brief Get the singleton instance of DatabaseManager
     * @return Reference to the DatabaseManager instance
     * 
     * Implements the singleton pattern to ensure only one database connection
     * exists throughout the application lifecycle.
     */
    static DatabaseManager& getInstance();

    /**
     * @brief Connect to the SQLite database
     * @return True if connection successful, false otherwise
     * 
     * Establishes a connection to the SQLite database and enables foreign key constraints.
     * If already connected, returns true immediately.
     */
    bool connect();

    /**
     * @brief Disconnect from the SQLite database
     * 
     * Closes the database connection and resets connection state.
     * Also resets transaction state if a transaction was in progress.
     */
    void disconnect();

    /**
     * @brief Check if database is connected
     * @return True if connected, false otherwise
     * 
     * Verifies both the connection flag and database pointer are valid.
     */
    bool isConnected() const;

    /**
     * @brief Execute a SQL query (INSERT, UPDATE, DELETE)
     * @param query The SQL query string to execute
     * @return True if query executed successfully, false otherwise
     * 
     * Executes SQL queries that don't return data (INSERT, UPDATE, DELETE).
     * Prints error messages if the query fails.
     */
    bool executeQuery(const std::string& query);

    /**
     * @brief Execute a SELECT query and return results
     * @param query The SQL SELECT query string
     * @return Vector of vectors containing query results as strings
     * 
     * Executes SELECT queries and returns the results as a vector of string vectors.
     * Each inner vector represents a row, and each string represents a column value.
     * Uses prepared statements for safe query execution.
     */
    std::vector<std::vector<std::string>> executeSelect(const std::string& query);

    /**
     * @brief Execute an INSERT query and return the new row ID
     * @param query The SQL INSERT query string
     * @return The ID of the newly inserted row, or -1 if failed
     * 
     * Executes INSERT queries and returns the auto-generated row ID.
     * Useful for getting the primary key of newly inserted records.
     */
    int executeInsert(const std::string& query);

    /**
     * @brief Execute an UPDATE query
     * @param query The SQL UPDATE query string
     * @return True if query executed successfully, false otherwise
     * 
     * Wrapper around executeQuery for UPDATE operations.
     */
    bool executeUpdate(const std::string& query);

    /**
     * @brief Execute a DELETE query
     * @param query The SQL DELETE query string
     * @return True if query executed successfully, false otherwise
     * 
     * Wrapper around executeQuery for DELETE operations.
     */
    bool executeDelete(const std::string& query);

    /**
     * @brief Begin a database transaction
     * @return True if transaction started successfully, false otherwise
     * 
     * Starts a new database transaction. If already in a transaction, returns true.
     * All subsequent operations will be part of this transaction until committed or rolled back.
     */
    bool beginTransaction();

    /**
     * @brief Commit the current transaction
     * @return True if transaction committed successfully, false otherwise
     * 
     * Commits all changes made since the last beginTransaction() call.
     * If not in a transaction, returns true immediately.
     */
    bool commitTransaction();

    /**
     * @brief Rollback the current transaction
     * @return True if transaction rolled back successfully, false otherwise
     * 
     * Discards all changes made since the last beginTransaction() call.
     * If not in a transaction, returns true immediately.
     */
    bool rollbackTransaction();
};
 
 #endif
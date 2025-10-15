/**
 * @file databaseManager.cpp
 * @brief Implementation of DatabaseManager class for SQLite database operations
 */

#include "../include/databaseManager.hpp"
#include <iostream>
#include <stdexcept>

// ============================================================================
// STATIC MEMBER INITIALIZATION
// ============================================================================

std::unique_ptr<DatabaseManager> DatabaseManager::instance = nullptr;

// ============================================================================
// CONSTRUCTOR
// ============================================================================

/**
 * @brief Constructor implementation
 * 
 * Initializes the database manager with default settings.
 * Sets the database path and initializes connection state.
 */
DatabaseManager::DatabaseManager() : db(nullptr), isConnected_(false), inTransaction(false) {
    dbPath = "database/cs1d_lab3.db";
}

// ============================================================================
// SINGLETON PATTERN
// ============================================================================

/**
 * @brief Get the singleton instance of DatabaseManager
 * @return Reference to the DatabaseManager instance
 * 
 * Implements the singleton pattern to ensure only one database connection
 * exists throughout the application lifecycle.
 */
DatabaseManager& DatabaseManager::getInstance() {
    if (instance == nullptr) {
        instance = std::unique_ptr<DatabaseManager>(new DatabaseManager());
    }
    return *instance;
}

// ============================================================================
// CONNECTION MANAGEMENT
// ============================================================================

/**
 * @brief Connect to the SQLite database
 * @return True if connection successful, false otherwise
 * 
 * Establishes a connection to the SQLite database and enables foreign key constraints.
 * If already connected, returns true immediately.
 */
bool DatabaseManager::connect() {
    if (isConnected_) {
        return true;
    }
    
    int rc = sqlite3_open(dbPath.c_str(), &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    
    // Enable foreign key constraints (disabled by default in SQLite)
    char* errMsg = nullptr;
    rc = sqlite3_exec(db, "PRAGMA foreign_keys = ON;", nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error enabling foreign keys: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return false;
    }
    
    isConnected_ = true;
    std::cout << "Connected to SQLite database: " << dbPath << std::endl;
    std::cout << "✅ Foreign key constraints enabled" << std::endl;
    return true;
}

/**
 * @brief Disconnect from the SQLite database
 * 
 * Closes the database connection and resets connection state.
 * Also resets transaction state if a transaction was in progress.
 */
void DatabaseManager::disconnect() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
    isConnected_ = false;
    inTransaction = false;
    std::cout << "Disconnected from database" << std::endl;
}

/**
 * @brief Check if database is connected
 * @return True if connected, false otherwise
 * 
 * Verifies both the connection flag and database pointer are valid.
 */
bool DatabaseManager::isConnected() const {
    return isConnected_ && db != nullptr;
}

// ============================================================================
// QUERY EXECUTION
// ============================================================================

/**
 * @brief Execute a SQL query (INSERT, UPDATE, DELETE)
 * @param query The SQL query string to execute
 * @return True if query executed successfully, false otherwise
 * 
 * Executes SQL queries that don't return data (INSERT, UPDATE, DELETE).
 * Prints error messages if the query fails.
 */
bool DatabaseManager::executeQuery(const std::string& query) {
    if (!isConnected()) {
        std::cerr << "Database not connected" << std::endl;
        return false;
    }
    
    char* errMsg = 0;
    int rc = sqlite3_exec(db, query.c_str(), 0, 0, &errMsg);
    
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    
    return true;
}

/**
 * @brief Execute a SELECT query and return results
 * @param query The SQL SELECT query string
 * @return Vector of vectors containing query results as strings
 * 
 * Executes SELECT queries and returns the results as a vector of string vectors.
 * Each inner vector represents a row, and each string represents a column value.
 * Uses prepared statements for safe query execution.
 */
V<std::vector<std::string>> DatabaseManager::executeSelect(const std::string& query) {
    V<std::vector<std::string>> results;
    
    if (!isConnected()) {
        std::cerr << "Database not connected" << std::endl;
        return results;
    }
    
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return results;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::vector<std::string> row;
        int columnCount = sqlite3_column_count(stmt);
        
        for (int i = 0; i < columnCount; i++) {
            const char* value = (const char*)sqlite3_column_text(stmt, i);
            row.push_back(value ? std::string(value) : "");
        }
        results.push_back(row);
    }
    
    sqlite3_finalize(stmt);
    return results;
}

/**
 * @brief Execute an INSERT query and return the new row ID
 * @param query The SQL INSERT query string
 * @return The ID of the newly inserted row, or -1 if failed
 * 
 * Executes INSERT queries and returns the auto-generated row ID.
 * Useful for getting the primary key of newly inserted records.
 */
int DatabaseManager::executeInsert(const std::string& query) {
    if (!isConnected()) {
        std::cerr << "Database not connected" << std::endl;
        return -1;
    }
    
    char* errMsg = 0;
    int rc = sqlite3_exec(db, query.c_str(), 0, 0, &errMsg);
    
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return -1;
    }
    
    return sqlite3_last_insert_rowid(db);
}

/**
 * @brief Execute an UPDATE query
 * @param query The SQL UPDATE query string
 * @return True if query executed successfully, false otherwise
 * 
 * Wrapper around executeQuery for UPDATE operations.
 */
bool DatabaseManager::executeUpdate(const std::string& query) {
    return executeQuery(query);
}

/**
 * @brief Execute a DELETE query
 * @param query The SQL DELETE query string
 * @return True if query executed successfully, false otherwise
 * 
 * Wrapper around executeQuery for DELETE operations.
 */
bool DatabaseManager::executeDelete(const std::string& query) {
    return executeQuery(query);
}

// ============================================================================
// TRANSACTION MANAGEMENT
// ============================================================================

/**
 * @brief Begin a database transaction
 * @return True if transaction started successfully, false otherwise
 * 
 * Starts a new database transaction. If already in a transaction, returns true.
 * All subsequent operations will be part of this transaction until committed or rolled back.
 */
bool DatabaseManager::beginTransaction() {
    if (inTransaction) {
        return true;
    }
    
    bool result = executeQuery("BEGIN TRANSACTION;");
    if (result) {
        inTransaction = true;
    }
    return result;
}

/**
 * @brief Commit the current transaction
 * @return True if transaction committed successfully, false otherwise
 * 
 * Commits all changes made since the last beginTransaction() call.
 * If not in a transaction, returns true immediately.
 */
bool DatabaseManager::commitTransaction() {
    if (!inTransaction) {
        return true;
    }
    
    bool result = executeQuery("COMMIT;");
    if (result) {
        inTransaction = false;
    }
    return result;
}

/**
 * @brief Rollback the current transaction
 * @return True if transaction rolled back successfully, false otherwise
 * 
 * Discards all changes made since the last beginTransaction() call.
 * If not in a transaction, returns true immediately.
 */
bool DatabaseManager::rollbackTransaction() {
    if (!inTransaction) {
        return true;
    }
    
    bool result = executeQuery("ROLLBACK;");
    if (result) {
        inTransaction = false;
    }
    return result;
}

// ============================================================================
// DESTRUCTOR
// ============================================================================

/**
 * @brief Destructor implementation
 * 
 * Ensures proper cleanup by disconnecting from the database
 * when the DatabaseManager instance is destroyed.
 */
DatabaseManager::~DatabaseManager() {
    disconnect();
}

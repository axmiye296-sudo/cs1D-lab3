/**
 * SQLite Database Manager Implementation
 * Handles SQLite database operations
 */

#include "../include/databaseManager.hpp"
#include <iostream>
#include <stdexcept>

std::unique_ptr<DatabaseManager> DatabaseManager::instance = nullptr;

DatabaseManager::DatabaseManager() : db(nullptr), isConnected_(false), inTransaction(false) {
    dbPath = "database/cs1d_lab3.db";
}

DatabaseManager& DatabaseManager::getInstance() {
    if (instance == nullptr) {
        instance = std::unique_ptr<DatabaseManager>(new DatabaseManager());
    }
    return *instance;
}

bool DatabaseManager::connect() {
    if (isConnected_) {
        return true;
    }
    
    int rc = sqlite3_open(dbPath.c_str(), &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    
    isConnected_ = true;
    std::cout << "Connected to SQLite database: " << dbPath << std::endl;
    return true;
}

void DatabaseManager::disconnect() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
    isConnected_ = false;
    inTransaction = false;
    std::cout << "Disconnected from database" << std::endl;
}

bool DatabaseManager::isConnected() const {
    return isConnected_ && db != nullptr;
}

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

bool DatabaseManager::executeUpdate(const std::string& query) {
    return executeQuery(query);
}

bool DatabaseManager::executeDelete(const std::string& query) {
    return executeQuery(query);
}

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

DatabaseManager::~DatabaseManager() {
    disconnect();
}

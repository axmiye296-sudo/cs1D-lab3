/**
 * SQLite Database Manager
 * Handles SQLite database connections and operations
 */

#ifndef DATABASE_MANAGER_HPP
#define DATABASE_MANAGER_HPP

#include "header.hpp"
#include "databaseInterface.hpp"
#include <sqlite3.h>

class DatabaseManager : public DatabaseInterface {
private:
    static std::unique_ptr<DatabaseManager> instance;
    std::string dbPath;
    sqlite3* db;
    bool isConnected_;
    bool inTransaction;

    DatabaseManager();

public:
    static DatabaseManager& getInstance();
    
    // Connection management
    bool connect() override;
    void disconnect() override;
    bool isConnected() const override;
    
    // Generic query execution
    bool executeQuery(const std::string& query) override;
    V<std::vector<std::string>> executeSelect(const std::string& query) override;
    int executeInsert(const std::string& query) override;
    bool executeUpdate(const std::string& query) override;
    bool executeDelete(const std::string& query) override;
    
    // Transaction management
    bool beginTransaction() override;
    bool commitTransaction() override;
    bool rollbackTransaction() override;
    
    ~DatabaseManager();
};

#endif
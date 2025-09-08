#ifndef DATABASE_MANAGER_HPP
#define DATABASE_MANAGER_HPP

#include "header.hpp"
#include <pqxx/pqxx>

class DatabaseManager {
private:
    static std::unique_ptr<DatabaseManager> instance;
    std::string connectionString;
    std::unique_ptr<pqxx::connection> connection;
    bool isConnected_;

    DatabaseManager();

public:
    static DatabaseManager& getInstance();

    // Connection management
    bool connect();
    void disconnect();
    bool isConnected() const;

    // Generic query execution
    bool executeQuery(const std::string& query);
    V<std::vector<std::string>> executeSelect(const std::string& query);
    int executeInsert(const std::string& query);
    bool executeUpdate(const std::string& query);
    bool executeDelete(const std::string& query);

    // Transaction management
    bool beginTransaction();
    bool commitTransaction();
    bool rollbackTransaction();

    ~DatabaseManager();
};

#endif
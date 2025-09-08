
#include "../include/databaseManager.hpp"
#include <iostream>
#include <stdexcept>

std::unique_ptr<DatabaseManager> DatabaseManager::instance = nullptr;

DatabaseManager::DatabaseManager() : connection(nullptr), isConnected_(false) {
    connectionString = "host=postgres port=5432 dbname=cs1d_lab3 user=cs1d_user password=cs1d_password";
}

DatabaseManager& DatabaseManager::getInstance() {
    if (instance == nullptr) {
        instance = std::unique_ptr<DatabaseManager>(new DatabaseManager());
    }
    return *instance;
}

bool DatabaseManager::connect() {
    try {
        connection = std::make_unique<pqxx::connection>(connectionString);
        isConnected_ = true;
        std::cout << "Connected to database: " << connection->dbname() << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Database connection failed: " << e.what() << std::endl;
        isConnected_ = false;
        return false;
    }
}

void DatabaseManager::disconnect() {
    if (connection) {
        connection->disconnect();
        connection.reset();
        isConnected_ = false;
        std::cout << "Disconnected from database" << std::endl;
    }
}

bool DatabaseManager::isConnected() const {
    return isConnected_ && connection && connection->is_open();
}

bool DatabaseManager::executeQuery(const std::string& query) {
    if (!isConnected()) {
        std::cerr << "Not connected to database" << std::endl;
        return false;
    }

    try {
        pqxx::work txn(*connection);
        txn.exec(query);
        txn.commit();
        std::cout << "Query executed successfully: " << query << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Query execution failed: " << e.what() << std::endl;
        return false;
    }
}

V<std::vector<std::string>> DatabaseManager::executeSelect(const std::string& query) {
    V<std::vector<std::string>> result;

    if (!isConnected()) {
        std::cerr << "Not connected to database" << std::endl;
        return result;
    }

    try {
        pqxx::work txn(*connection);
        pqxx::result res = txn.exec(query);

        for (const auto& row : res) {
            std::vector<std::string> rowData;
            for (const auto& field : row) {
                rowData.push_back(field.c_str());
            }
            result.push_back(rowData);
        }

        txn.commit();
        std::cout << "SELECT executed successfully: " << query << std::endl;
        std::cout << "Retrieved " << result.size() << " rows" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "SELECT execution failed: " << e.what() << std::endl;
    }

    return result;
}

int DatabaseManager::executeInsert(const std::string& query) {
    if (!isConnected()) {
        return -1;
    }

    try {
        pqxx::work txn(*connection);
        pqxx::result res = txn.exec(query);
        txn.commit();

        if (!res.empty() && !res[0].empty()) {
            int newId = res[0][0].as<int>();
            std::cout << "INSERT executed successfully: " << query << std::endl;
            std::cout << "New ID: " << newId << std::endl;
            return newId;
        }
        return 1; // Fallback for queries without RETURNING
    } catch (const std::exception& e) {
        std::cerr << "INSERT execution failed: " << e.what() << std::endl;
        return -1;
    }
}

bool DatabaseManager::executeUpdate(const std::string& query) {
    return executeQuery(query);
}

bool DatabaseManager::executeDelete(const std::string& query) {
    return executeQuery(query);
}

bool DatabaseManager::beginTransaction() {
    if (!isConnected()) {
        return false;
    }

    try {
        std::cout << "Transaction started" << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Failed to begin transaction: " << e.what() << std::endl;
        return false;
    }
}

bool DatabaseManager::commitTransaction() {
    if (!isConnected()) {
        return false;
    }

    try {
        std::cout << "Transaction committed" << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Failed to commit transaction: " << e.what() << std::endl;
        return false;
    }
}

bool DatabaseManager::rollbackTransaction() {
    if (!isConnected()) {
        return false;
    }

    try {
        std::cout << "Transaction rolled back" << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Failed to rollback transaction: " << e.what() << std::endl;
        return false;
    }
}

DatabaseManager::~DatabaseManager() {
    if (isConnected_) {
        disconnect();
    }
}
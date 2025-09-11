#include "../include/mockDatabaseManager.hpp"
#include <iostream>

std::unique_ptr<MockDatabaseManager> MockDatabaseManager::instance = nullptr;

MockDatabaseManager::MockDatabaseManager() : isConnected_(false) {}

MockDatabaseManager& MockDatabaseManager::getInstance() {
    if (instance == nullptr) {
        instance = std::unique_ptr<MockDatabaseManager>(new MockDatabaseManager());
    }
    return *instance;
}

bool MockDatabaseManager::connect() {
    isConnected_ = true;
    std::cout << "Connected to MOCK database" << std::endl;
    return true;
}

void MockDatabaseManager::disconnect() {
    isConnected_ = false;
    std::cout << "Disconnected from MOCK database" << std::endl;
}

bool MockDatabaseManager::isConnected() const {
    return isConnected_;
}

V<std::vector<std::string>> MockDatabaseManager::executeSelect(const std::string& query) {
    V<std::vector<std::string>> result;
    
    std::cout << "MOCK: executeSelect - " << query << std::endl;
    
    // Handle different table queries
    if (query.find("FROM cities") != std::string::npos) {
        result.push_back({"1", "New York"});
        result.push_back({"2", "Los Angeles"});
        result.push_back({"3", "Chicago"});
    }
    else if (query.find("FROM foods") != std::string::npos) {
        result.push_back({"1", "Pizza", "1", "15.99"});
        result.push_back({"2", "Burger", "1", "12.50"});
        result.push_back({"3", "Tacos", "2", "8.99"});
    }
    else if (query.find("FROM users") != std::string::npos) {
        result.push_back({"1", "John Doe", "admin"});
        result.push_back({"2", "Jane Smith", "user"});
        result.push_back({"3", "Bob Johnson", "user"});
    }
    else if (query.find("FROM trip_cities") != std::string::npos) {
        // Add some mock trip_cities data
        result.push_back({"1", "1", "1", "1"});  // id, trip_id, city_id, visit_order
        result.push_back({"2", "1", "2", "2"});
        result.push_back({"3", "2", "3", "1"});
    }
    else if (query.find("FROM trips") != std::string::npos) {
        result.push_back({"1", "1", "business", "3234.7"});
        result.push_back({"2", "2", "leisure", "1756.3"});
    }
    else if (query.find("FROM purchases") != std::string::npos) {
        result.push_back({"1", "1", "1", "2", "1"});
        result.push_back({"2", "1", "2", "1", "1"});
    }
    else if (query.find("FROM city_distances") != std::string::npos) {
        result.push_back({"1", "2", "2445.5"});
        result.push_back({"1", "3", "789.2"});
    }
    
    std::cout << "MOCK: Returning " << result.size() << " rows" << std::endl;
    return result;
}

bool MockDatabaseManager::executeQuery(const std::string& query) {
    std::cout << "MOCK: executeQuery - " << query << std::endl;
    return true;
}

int MockDatabaseManager::executeInsert(const std::string& query) {
    std::cout << "MOCK: executeInsert - " << query << std::endl;
    return 1; // Mock always returns ID 1
}

bool MockDatabaseManager::executeUpdate(const std::string& query) {
    std::cout << "MOCK: executeUpdate - " << query << std::endl;
    return true;
}

bool MockDatabaseManager::executeDelete(const std::string& query) {
    std::cout << "MOCK: executeDelete - " << query << std::endl;
    return true;
}

bool MockDatabaseManager::beginTransaction() {
    std::cout << "MOCK: Transaction started" << std::endl;
    return true;
}

bool MockDatabaseManager::commitTransaction() {
    std::cout << "MOCK: Transaction committed" << std::endl;
    return true;
}

bool MockDatabaseManager::rollbackTransaction() {
    std::cout << "MOCK: Transaction rolled back" << std::endl;
    return true;
}

MockDatabaseManager::~MockDatabaseManager() {
    if (isConnected_) {
        disconnect();
    }
}

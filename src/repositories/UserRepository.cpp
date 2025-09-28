/**
 * @file UserRepository.cpp
 * @brief Implementation of UserRepository class for database operations
 * @author CS1D
 * @date 2025
 * 
 * This file contains the data access layer implementation for managing
 * user entities in the SQLite database. It handles all CRUD
 * operations and query building for the users table.
 */

#include "../include/repositories/UserRepository.hpp"
#include <iostream>

/**
 * @brief Constructor for UserRepository
 * @param database Reference to DatabaseManager for SQLite operations
 * 
 * Initializes the repository with a database manager instance.
 * All database operations will be performed through this manager.
 */
UserRepository::UserRepository(DatabaseManager& database) : db(database) {}

/**
 * @brief Saves a User entity to the database
 * @param user Reference to User object to save
 * @return true if save operation was successful, false otherwise
 * 
 * Determines whether to insert a new record or update an existing one
 * based on the entity's ID. If ID is 0, performs INSERT; otherwise UPDATE.
 */
bool UserRepository::save(User& user) {
    std::string query;
    if (user.getId() == 0) {
        query = buildInsertQuery(user);
    } else {
        query = buildUpdateQuery(user);
    }
    return db.executeQuery(query);
}

/**
 * @brief Loads a specific User record by ID
 * @param id The ID of the record to load
 * @param user Reference to User object to populate
 * @return true if record was found and loaded, false otherwise
 */
bool UserRepository::load(int id, User& user) {
    std::string query = buildSelectQuery(id);
    auto dbResult = db.executeSelect(query);

    if (!dbResult.empty() && dbResult[0].size() >= 3) {
        user = mapRowToEntity(dbResult[0]);
        return true;
    }
    return false;
}

/**
 * @brief Removes a User record by ID
 * @param id The ID of the record to delete
 * @return true if deletion was successful, false otherwise
 */
bool UserRepository::remove(int id) {
    std::string query = buildDeleteQuery(id);
    return db.executeQuery(query);
}

/**
 * @brief Retrieves all User records from the database
 * @return V<User> Vector of all User objects
 */
V<User> UserRepository::findAll() {
    V<User> result;
    std::string query = buildSelectAllQuery();
    auto dbResult = db.executeSelect(query);

    if (!dbResult.empty()) {
        for (const auto& row : dbResult) {
            if (row.size() >= 3) {
                User user = mapRowToEntity(row);
                result.push_back(user);
            }
        }
    }
    return result;
}

/**
 * @brief Finds users by name
 * @param name The name to search for
 * @return V<User> Vector of User objects with matching name
 */
V<User> UserRepository::findByName(const std::string& name) {
    V<User> result;
    std::string query = "SELECT id, name, role FROM users WHERE name = '" + name + "';";
    auto dbResult = db.executeSelect(query);

    for (const auto& row : dbResult) {
        if (row.size() >= 3) {
            result.push_back(mapRowToEntity(row));
        }
    }
    return result;
}

/**
 * @brief Finds users by role
 * @param role The role to search for
 * @return V<User> Vector of User objects with matching role
 */
V<User> UserRepository::findByRole(const std::string& role) {
    V<User> result;
    std::string query = "SELECT id, name, role FROM users WHERE role = '" + role + "';";
    auto dbResult = db.executeSelect(query);

    for (const auto& row : dbResult) {
        if (row.size() >= 3) {
            result.push_back(mapRowToEntity(row));
        }
    }
    return result;
}

// ============================================================================
// HELPER METHODS
// ============================================================================

User UserRepository::mapRowToEntity(const std::vector<std::string>& row) {
    int id = std::stoi(row[0]);
    std::string name = row[1];
    std::string role = row[2];
    return User(name, id, role);
}

std::string UserRepository::buildInsertQuery(const User& user) {
    return "INSERT INTO users (name, role) VALUES ('" + user.getName() + "', '" + user.getRole() + "');";
}

std::string UserRepository::buildUpdateQuery(const User& user) {
    return "UPDATE users SET name = '" + user.getName() +
           "', role = '" + user.getRole() +
           "' WHERE id = " + std::to_string(user.getId()) + ";";
}

std::string UserRepository::buildDeleteQuery(int id) {
    return "DELETE FROM users WHERE id = " + std::to_string(id) + ";";
}

std::string UserRepository::buildSelectQuery(int id) {
    return "SELECT id, name, role FROM users WHERE id = " + std::to_string(id) + ";";
}

std::string UserRepository::buildSelectAllQuery() {
    return "SELECT id, name, role FROM users ORDER BY id;";
}

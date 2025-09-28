/**
 * @file UserService.cpp
 * @brief Implementation of UserService class for managing user operations
 * @author 
 * @date 2025
 * 
 * This file contains the business logic implementation for managing users,
 * including adding, removing, updating, and searching users.
 */

#include "../include/services/UserService.hpp"
#include <iostream>
#include <iomanip>

/**
 * @brief Constructor for UserService
 * @param repository Reference to UserRepository for data access
 * 
 * Initializes the service with a repository instance for database operations.
 * The repository handles all direct database interactions while the service
 * provides business logic and validation.
 */
UserService::UserService(UserRepository& repository) : repo(repository) {}

/**
 * @brief Adds a new user to the system
 * @param name The user's name
 * @param role The user's role
 * @return true if user was successfully added, false otherwise
 * 
 * This method handles the complete process of adding a user:
 * 1. Validates parameters
 * 2. Creates User entity and saves to database
 */
bool UserService::addUser(const std::string& name, const std::string& role) {
    if (!validateUser(name, role)) {
        return false;
    }
    User user(name, 0, role); // ID handled by database
    return repo.save(user);
}

/**
 * @brief Retrieves all users
 * @return V<User> Vector of all User objects
 * 
 * Returns all users stored in the database.
 */
V<User> UserService::getAllUsers() {
    return repo.findAll();
}

/**
 * @brief Removes a user by ID
 * @param id The ID of the user to remove
 * @return true if user was successfully removed, false otherwise
 */
bool UserService::removeUser(int id) {
    if (id <= 0) {
        std::cerr << "Error: Invalid user ID (" << id << ")" << std::endl;
        return false;
    }
    return repo.remove(id);
}

/**
 * @brief Updates a user's details
 * @param id The user's ID
 * @param name The new name
 * @param role The new role
 * @return true if user was successfully updated, false otherwise
 */
bool UserService::updateUser(int id, const std::string& name, const std::string& role) {
    if (id <= 0 || !validateUser(name, role)) {
        return false;
    }
    User user(name, id, role);
    return repo.save(user);
}

/**
 * @brief Finds users by name
 * @param name The name to search
 * @return V<User> Vector of matching users
 */
V<User> UserService::findUsersByName(const std::string& name) {
    return repo.findByName(name);
}

/**
 * @brief Finds users by role
 * @param role The role to search
 * @return V<User> Vector of matching users
 */
V<User> UserService::findUsersByRole(const std::string& role) {
    return repo.findByRole(role);
}

/**
 * @brief Prints all users in a formatted table
 * 
 * Displays a formatted table showing all users in the system,
 * including their IDs, names, and roles.
 */
void UserService::printAllUsers() {
    V<User> users = getAllUsers();

    std::cout << "\n=== User List ===" << std::endl;

    if (users.empty()) {
        std::cout << "No users found." << std::endl;
        return;
    }

    std::cout << std::setw(5) << "ID" << " | "
              << std::setw(20) << "Name" << " | "
              << std::setw(15) << "Role" << std::endl;
    std::cout << std::string(45, '-') << std::endl;

    for (const auto& user : users) {
        std::cout << std::setw(5) << user.getId() << " | "
                  << std::setw(20) << user.getName() << " | "
                  << std::setw(15) << user.getRole() << std::endl;
    }

    std::cout << "Total users: " << users.size() << std::endl;
}

/**
 * @brief Validates user parameters
 * @param name The user name to validate
 * @param role The user role to validate
 * @return true if all parameters are valid, false otherwise
 * 
 * Performs basic validation on the input parameters:
 * - Name must not be empty
 * - Role must not be empty
 */
bool UserService::validateUser(const std::string& name, const std::string& role) {
    if (name.empty() || role.empty()) {
        std::cerr << "Error: Invalid user parameters (name: '" << name
                  << "', role: '" << role << "')" << std::endl;
        return false;
    }
    return true;
}

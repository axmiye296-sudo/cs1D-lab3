#ifndef USER_SERVICE_HPP
#define USER_SERVICE_HPP

#include "../header.hpp"
#include "../repositories/UserRepository.hpp"
#include "../entities/User.hpp"
#include <iomanip>

/**
 * @class UserService
 * @brief Service layer for User business logic and operations
 * 
 * This class contains the business logic for managing users.
 * It acts as an intermediary between the presentation layer and repository layer,
 * enforcing business rules and providing a clean API for user operations.
 */
class UserService {
private:
    UserRepository& repo; ///< Reference to the User repository

public:
    /**
     * @brief Constructor
     * @param repository Reference to the User repository
     */
    UserService(UserRepository& repository);

    // Core operations
    /**
     * @brief Add a new user with validation
     * @param name The name of the user
     * @param role The role of the user
     * @return true if successful, false otherwise
     * @note Automatically assigns ID via database auto-increment
     */
    bool addUser(const std::string& name, const std::string& role);

    /**
     * @brief Get all users
     * @return Vector of all User objects
     */
    V<User> getAllUsers();

    /**
     * @brief Remove a user by ID
     * @param id The ID of the user to remove
     * @return true if successful, false otherwise
     */
    bool removeUser(int id);

    /**
     * @brief Update user details
     * @param id The ID of the user to update
     * @param name The new name
     * @param role The new role
     * @return true if successful, false otherwise
     */
    bool updateUser(int id, const std::string& name, const std::string& role);

    // Utility operations
    /**
     * @brief Find users by name
     * @param name The name to search
     * @return Vector of matching User objects
     */
    V<User> findUsersByName(const std::string& name);

    /**
     * @brief Find users by role
     * @param role The role to search
     * @return Vector of matching User objects
     */
    V<User> findUsersByRole(const std::string& role);

    /**
     * @brief Display all users in a formatted table
     * @note Prints to console in a formatted table
     */
    void printAllUsers();

    // Validation
    /**
     * @brief Validate User parameters
     * @param name The user name to validate
     * @param role The user role to validate
     * @return true if valid, false otherwise
     * @note Valid parameters must not be empty
     */
    bool validateUser(const std::string& name, const std::string& role);
};

#endif // USER_SERVICE_HPP

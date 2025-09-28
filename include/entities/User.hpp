/**
 * ENTITY LAYER: User class
 */
#ifndef USER_HPP
#define USER_HPP

#include "V.hpp"

/**
 * @class User
 * @brief Represents a user in the system
 * 
 * This class stores information about a system user, including their
 * unique ID, name, and role (e.g., admin, manager, customer).
 */
class User {
private:
    int id;             ///< Unique identifier of the user
    std::string name;   ///< Name of the user
    std::string role;   ///< Role of the user in the system

public:
    /**
     * @brief Default constructor
     * 
     * Initializes a User with default values (id = 0, empty name and role).
     */
    User();

    /**
     * @brief Full constructor with all parameters
     * @param name The user's name
     * @param id The user's unique identifier
     * @param role The user's role in the system
     */
    User(std::string name, int id, std::string role);

    // Getters
    /**
     * @brief Get the user ID
     * @return The user's ID
     */
    int getId() const;

    /**
     * @brief Get the user's name
     * @return The user's name
     */
    std::string getName() const;

    /**
     * @brief Get the user's role
     * @return The user's role
     */
    std::string getRole() const;

    // Setters
    /**
     * @brief Set the user ID
     * @param i The new ID value
     */
    void setId(int i);

    /**
     * @brief Set the user's name
     * @param s The new name
     */
    void setName(std::string s);

    /**
     * @brief Set the user's role
     * @param r The new role
     */
    void setRole(std::string r);

    // Validation
    /**
     * @brief Validate if the User object has valid data
     * @return true if id > 0, name and role are not empty; false otherwise
     */
    bool isValid() const;

    // Utility Methods
    /**
     * @brief Convert User to string representation
     * @return Formatted string with user details
     */
    std::string toString() const;

    /**
     * @brief Compare two User objects for equality
     * @param other The other User object
     * @return true if all fields match, false otherwise
     */
    bool equals(const User& other) const;
};

#endif // USER_HPP
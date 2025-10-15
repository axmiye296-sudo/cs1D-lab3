/**
 * @file Admin.cpp
 * @brief Implementation of Admin entity class
 */

#include "../../include/entities/Admin.hpp"
#include <iostream>

// ============================================================================
// CONSTRUCTORS
// ============================================================================

/**
 * @brief Default constructor implementation
 * 
 * Creates an Admin object with default credentials:
 * - Username: "admin"
 * - Password: "password" 
 * - Login status: false
 */
Admin::Admin() : username("admin"), password("password"), isLoggedIn(false) {}

/**
 * @brief Parameterized constructor implementation
 * @param username The admin's username
 * @param password The admin's password
 * 
 * Creates an Admin object with the specified credentials.
 * Login status is initialized to false.
 */
Admin::Admin(const std::string& username, const std::string& password) 
    : username(username), password(password), isLoggedIn(false) {}

// ============================================================================
// GETTERS
// ============================================================================

/**
 * @brief Get the admin's username
 * @return The username as a string
 */
std::string Admin::getUsername() const {
    return username;
}

/**
 * @brief Get the admin's password
 * @return The password as a string
 */
std::string Admin::getPassword() const {
    return password;
}

/**
 * @brief Get the current login status
 * @return True if logged in, false otherwise
 */
bool Admin::getIsLoggedIn() const {
    return isLoggedIn;
}

// ============================================================================
// SETTERS
// ============================================================================

/**
 * @brief Set the admin's username
 * @param username The new username
 */
void Admin::setUsername(const std::string& username) {
    this->username = username;
}

/**
 * @brief Set the admin's password
 * @param password The new password
 */
void Admin::setPassword(const std::string& password) {
    this->password = password;
}

/**
 * @brief Set the login status
 * @param loggedIn The new login status
 */
void Admin::setIsLoggedIn(bool loggedIn) {
    this->isLoggedIn = loggedIn;
}

// ============================================================================
// AUTHENTICATION METHODS
// ============================================================================

/**
 * @brief Attempt to log in with credentials
 * @param inputUsername The username to authenticate
 * @param inputPassword The password to authenticate
 * @return True if login successful, false otherwise
 * 
 * Compares the provided credentials with the stored credentials.
 * If they match, sets isLoggedIn to true and displays success message.
 * If they don't match, displays error message and returns false.
 */
bool Admin::login(const std::string& inputUsername, const std::string& inputPassword) {
    if (inputUsername == this->username && inputPassword == this->password) {
        this->isLoggedIn = true;
        std::cout << "Admin " << username << " logged in successfully!" << std::endl;
        return true;
    } else {
        std::cout << "Invalid username or password!" << std::endl;
        return false;
    }
}

/**
 * @brief Log out the admin
 * 
 * Sets isLoggedIn to false and displays logout message.
 * If admin is not currently logged in, displays an error message.
 */
void Admin::logout() {
    if (!isLoggedIn) {
        std::cout << "ERROR: Admin is not logged in." << std::endl;
        return;
    }
    else
    {
    this->isLoggedIn = false;
    std::cout << "Admin " << username << " logged out." << std::endl;
    }
}

// ============================================================================
// DISPLAY METHODS
// ============================================================================

/**
 * @brief Display admin information
 * 
 * Prints the admin's username and login status to the console.
 * Used for debugging and information display purposes.
 */
void Admin::displayInfo() const {
    std::cout << "Admin Info:" << std::endl;
    std::cout << "  Username: " << username << std::endl;
    std::cout << "  Logged In: " << (isLoggedIn ? "Yes" : "No") << std::endl;
}
/**
 * This file contains admin methods for loggining in/out and checking permissions
 */
#include "../../include/entities/Admin.hpp"
#include <iostream>

// Default constructor
Admin::Admin() : username("admin"), password("password"), isLoggedIn(false) {}

// Parameterized constructor
Admin::Admin(const std::string& username, const std::string& password) 
    : username(username), password(password), isLoggedIn(false) {}

// Getters

std::string Admin::getUsername() const {
    return username;
}

std::string Admin::getPassword() const {
    return password;
}

bool Admin::getIsLoggedIn() const {
    return isLoggedIn;
}

// Setters

void Admin::setUsername(const std::string& username) {
    this->username = username;
}

void Admin::setPassword(const std::string& password) {
    this->password = password;
}

void Admin::setIsLoggedIn(bool loggedIn) {
    this->isLoggedIn = loggedIn;
}

// Login function - simple version for beginners
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

void Admin::displayInfo() const {
    std::cout << "Admin Info:" << std::endl;
    std::cout << "  Username: " << username << std::endl;
    std::cout << "  Logged In: " << (isLoggedIn ? "Yes" : "No") << std::endl;
}
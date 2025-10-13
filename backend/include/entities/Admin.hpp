/**
 * This file is the header for the Admin entity containing function signatures.
 * Admin is only for log in/logout and permission checking. Does not actually
 * manage cities or foods directly. That is done in AdminService.
 */
#ifndef ADMIN_HPP
#define ADMIN_HPP

#include <string>

class Admin {
private:
    std::string username;   // Admin username
    std::string password;   // Admin password
    bool isLoggedIn;        // Admin login status - logged in or not

public:
    // Constructor
    Admin();
    Admin(const std::string& username, const std::string& password);

    // Getters
    std::string getUsername() const;
    std::string getPassword() const;
    bool getIsLoggedIn() const;

    // Setters
    void setUsername(const std::string& username);
    void setPassword(const std::string& password);
    void setIsLoggedIn(bool loggedIn);

    // Admin actions
    bool login(const std::string& username, const std::string& password);
    void logout();
    
    // Display info
    void displayInfo() const;
};

#endif
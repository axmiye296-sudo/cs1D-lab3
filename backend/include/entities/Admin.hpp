/**
 * @file Admin.hpp
 * @brief Admin entity class for authentication and permission management
 */

 #ifndef ADMIN_HPP
 #define ADMIN_HPP
 
 #include <string>
 
 /**
  * @class Admin
  * @brief Represents an administrative user with authentication capabilities
  * 
  * The Admin class handles user authentication, login/logout functionality,
  * and permission checking. It does not directly manage cities or foods -
  * that functionality is handled by AdminService.
  */
 class Admin {
 private:
     std::string username;   ///< Admin username for authentication
     std::string password;   ///< Admin password for authentication
     bool isLoggedIn;        ///< Current login status of the admin
 
 public:
     /**
      * @brief Default constructor
      * 
      * Creates an empty Admin object with default values.
      * Username and password are empty, isLoggedIn is false.
      */
     Admin();
     
     /**
      * @brief Parameterized constructor
      * @param username The admin's username
      * @param password The admin's password
      * 
      * Creates an Admin object with the specified credentials.
      * isLoggedIn is set to false by default.
      */
     Admin(const std::string& username, const std::string& password);
 
     // Getters
     /**
      * @brief Get the admin's username
      * @return The username as a string
      */
     std::string getUsername() const;
     
     /**
      * @brief Get the admin's password
      * @return The password as a string
      */
     std::string getPassword() const;
     
     /**
      * @brief Get the current login status
      * @return True if logged in, false otherwise
      */
     bool getIsLoggedIn() const;
 
     // Setters
     /**
      * @brief Set the admin's username
      * @param username The new username
      */
     void setUsername(const std::string& username);
     
     /**
      * @brief Set the admin's password
      * @param password The new password
      */
     void setPassword(const std::string& password);
     
     /**
      * @brief Set the login status
      * @param loggedIn The new login status
      */
     void setIsLoggedIn(bool loggedIn);
 
     // Admin actions
     /**
      * @brief Attempt to log in with credentials
      * @param username The username to authenticate
      * @param password The password to authenticate
      * @return True if login successful, false otherwise
      * 
      * Compares the provided credentials with the stored credentials.
      * If they match, sets isLoggedIn to true.
      */
     bool login(const std::string& username, const std::string& password);
     
     /**
      * @brief Log out the admin
      * 
      * Sets isLoggedIn to false, effectively logging out the admin.
      */
     void logout();
     
     /**
      * @brief Display admin information
      * 
      * Prints the admin's username and login status to the console.
      * Used for debugging and information display purposes.
      */
     void displayInfo() const;
 };
 
 #endif
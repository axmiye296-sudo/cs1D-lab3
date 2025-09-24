/**
 * @file main.cpp
 * @brief Main entry point for the CS1D Lab 3 Trip Planning Application
 * @author CS1D Lab 3 Team
 * @date 2025
 * 
 * This file contains the main function that serves as the entry point
 * for the trip planning application. It initializes the application
 * and starts the main menu system.
 */

#include "../include/header.hpp"
#include "../include/databaseManager.hpp"

/**
 * @brief Main entry point of the application
 * @return int Exit status code (0 for success)
 * 
 * This function serves as the entry point for the trip planning application.
 * It displays the main menu and handles user menu choices in a loop until
 * the user chooses to quit.
 * 
 * The application flow:
 * 1. Display the main menu
 * 2. Handle user menu choice
 * 3. Continue until user chooses to quit
 * 
 * @note This is a simple implementation that will be enhanced with
 *       proper database integration and user management in future iterations.
 */
int main() {
    DatabaseManager& database = DatabaseManager::getInstance();

    // Connect to database
    if (!database.connect()) {
        std::cerr << "Failed to connect to database!" << std::endl;
        return 1;
    }

    // Main application loop
    while (true) {
        displayMainMenu();
        int result = handleMenuChoice(database);

        if (result == 0) {
            break;  // User chose to quit
        }
    }

    // Disconnect from database
    database.disconnect();

    return 0;
}
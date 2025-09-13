/**
 * @file main.cpp
 * @brief Main entry point for the CS1D Lab 3 Trip Planning Application
 * @author CS1D Lab 3 Team
 * @date 2024
 * 
 * This file contains the main function that serves as the entry point
 * for the trip planning application. It initializes the application
 * and starts the main menu system.
 */

#include "../include/header.hpp"

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
    displayMainMenu();
    handleMenuChoice();

    return 0;
}
/**
 * @file menu.cpp
 * @brief Simple menu interface for the Trip Planning Application
 */

#include "../include/header.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include "../include/repositories/CityRepository.hpp"
#include "../include/repositories/FoodRepository.hpp"
#include "../include/services/CityService.hpp"
#include "../include/services/FoodService.hpp"
#include "../include/databaseManager.hpp"

void displayMainMenu() {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "    Welcome to European Vacation - Trip Planning App" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    std::cout << "Plan your trips, explore cities, and discover local foods!" << std::endl;

    std::cout << "\n" << std::string(50, '-') << std::endl;
    std::cout << "                    MAIN MENU" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "1. Create Account" << std::endl;
    std::cout << "2. Login" << std::endl;
    std::cout << "3. List Cities and Foods" << std::endl;
    std::cout << "4. Create My Trip" << std::endl;
    std::cout << "5. Test Trip Service" << std::endl;
    std::cout << "0. Quit" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "\nEnter your choice (0-5): ";
}

int handleMenuChoice(DatabaseManager& database) {
    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            std::cout << "create new User function" << std::endl;
            break;
        case 2:
            std::cout << "login into account function" << std::endl;
            break;
        case 3:
            showCityAndFood(database);
            std::cin.ignore();
            std::cin.get();
            break;
        case 4:
            showTripController(database);        // ✅ Delegate to controller
            break;
        case 5:
            runTripTests(database);              // ✅ Delegate to test controller
            break;
        case 0:
            std::cout << "logout and quit" << std::endl;
            return 0;
        default:
            std::cout << "ERROR" << std::endl;
            break;
    }
    return 1;
}

void showCityAndFood(DatabaseManager& database) {
    CityRepository cityRepo(database);
    FoodRepository foodRepo(database);

    CityService cityService(cityRepo);
    FoodService foodService(foodRepo);

    cityService.displayCitiesWithFood(foodService);

    std::cin.ignore();
    std::cin.get();
}

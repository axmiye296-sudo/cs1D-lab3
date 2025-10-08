/**
 * This file is for testing admin login and admin services.
 * Changes will be saved to database so if testing please make sure to double 
 * check database before ending test.
 */

#include "../include/services/AdminService.hpp"
#include "../include/repositories/CityRepository.hpp"
#include "../include/repositories/FoodRepository.hpp"
#include "../include/databaseManager.hpp"
#include <iostream>

void showAdminMenu() {
    std::cout << "\n====== ADMIN MENU ======" << std::endl;
    std::cout << "1. Login as Admin" << std::endl;
    std::cout << "2. View All Cities" << std::endl;
    std::cout << "3. Add New City" << std::endl;
    std::cout << "4. Update City Name" << std::endl;
    std::cout << "5. View All Foods" << std::endl;
    std::cout << "6. Add Food to City" << std::endl;
    std::cout << "7. Delete City" << std::endl;
    std::cout << "8. Update Food Price" << std::endl;
    std::cout << "9. Update Food Name" << std::endl;
    std::cout << "10. Delete Food" << std::endl;
    std::cout << "11. View Foods for City" << std::endl;
    std::cout << "12. Logout" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "=========================" << std::endl;
    std::cout << "Choose an option: ";
}

int main() {
    std::cout << "Welcome to the Admin System!" << std::endl;
    std::cout << "Default admin credentials: username='admin', password='password'" << std::endl;

    // Initialize database
    DatabaseManager& database = DatabaseManager::getInstance();
    if (!database.connect()) {
        std::cerr << "Failed to connect to database!" << std::endl;
        return 1;
    }

    // Initialize repositories
    CityRepository cityRepo(database);
    FoodRepository foodRepo(database);

    // Initialize admin service
    AdminService adminService(cityRepo, foodRepo);

    int choice;
    std::string username, password, cityName, foodName;
    int cityId, foodId;
    double price;

    do {
        showAdminMenu();
        std::cin >> choice;

        switch (choice) {
            // LOG IN
            case 1: {
                std::cout << "Enter username: ";
                std::cin >> username;
                std::cout << "Enter password: ";
                std::cin >> password;
                adminService.loginAdmin(username, password);
                break;
            }
            // VIEW ALL CITIES
            case 2: {
                adminService.displayAllCities();
                break;
            }
            // ADD NEW CITY
            case 3: {
                std::cout << "Enter city name: ";
                std::cin.ignore();
                std::getline(std::cin, cityName);
                adminService.addNewCity(cityName);
                break;
            }
            // UPDATE CITY NAME
            case 4: {
                std::cout << "Enter city ID to update: ";
                std::cin >> cityId;
                std::cout << "Enter new city name: ";
                std::cin.ignore();
                std::getline(std::cin, cityName);
                adminService.updateCityName(cityId, cityName);
                break;
            }
            // VIEW ALL FOODS
            case 5: {
                adminService.displayAllFoods();
                break;
            }
            // ADD FOOD TO CITY
            case 6: {
                std::cout << "Enter city ID: ";
                std::cin >> cityId;
                std::cout << "Enter food name: ";
                std::cin.ignore();
                std::getline(std::cin, foodName);
                std::cout << "Enter price: $";
                std::cin >> price;
                adminService.addFoodToCity(cityId, foodName, price);
                break;
            }
            // DELETE CITY
            case 7: {
                std::cout << "Enter city ID to delete: ";
                std::cin >> cityId;
                adminService.deleteCity(cityId);
                break;
            }
            // UPDATE FOOD PRICE
            case 8: {
                std::cout << "Enter food ID: ";
                std::cin >> foodId;
                std::cout << "Enter new price: $";
                std::cin >> price;
                adminService.updateFoodPrice(foodId, price);
                break;
            }
            // UPDATE FOOD NAME
            case 9: {
                std::cout << "Enter food ID: ";
                std::cin >> foodId;
                std::cout << "Enter new food name: ";
                std::cin.ignore();
                std::getline(std::cin, foodName);
                adminService.updateFoodName(foodId, foodName);
                break;
            }
            // DELETE FOOD
            case 10: {
                std::cout << "Enter food ID to delete: ";
                std::cin >> foodId;
                adminService.deleteFood(foodId);
                break;
            }
            // VIEW FOODS FOR CITY
            case 11: {
                std::cout << "Enter city ID: ";
                std::cin >> cityId;
                adminService.displayFoodsForCity(cityId);
                break;
            }
            // LOG OUT
            case 12: {
                adminService.logoutAdmin();
                break;
            }
            // EXIT
            case 0: {
                std::cout << "Goodbye!" << std::endl;
                break;
            }
            // ERROR / INVALID OPTION
            default: {
                std::cout << "Invalid option. Please try again." << std::endl;
                break;
            }
        }

    } while (choice != 0);

    return 0;
}
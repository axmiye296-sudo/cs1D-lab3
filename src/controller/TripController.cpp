/**
 * @file TripController.cpp
 * @brief Controller for trip-related user interactions
 */

#include "../../include/controllers/TripController.hpp"
#include "../../include/repositories/TripRepository.hpp"
#include "../../include/repositories/TripCityRepository.hpp"
#include "../../include/repositories/CityRepository.hpp"
#include "../../include/repositories/FoodRepository.hpp"
#include "../../include/services/TripService.hpp"
#include "../../include/services/tripCityService.hpp"
#include "../../include/services/CityService.hpp"
#include "../../include/services/FoodService.hpp"
#include <iostream>
#include <iomanip>

void showTripController(DatabaseManager& database) {
    std::cout << "\n🚀 Initializing Trip Planning System..." << std::endl;

    try {
        // Initialize components
        CityRepository cityRepo(database);
        TripRepository tripRepo(database);
        TripCityRepository tripCityRepo(database);
        FoodRepository foodRepo(database);

        TripCityService tripCityService(tripCityRepo);
        FoodService foodService(foodRepo);
        TripService tripService(tripRepo, cityRepo, tripCityService, foodService);

        std::cout << "✅ System ready!" << std::endl;

        // Simple trip menu loop
        while (true) {
            displayTripMenu();

            int choice;
            std::cin >> choice;

            if (handleTripChoice(choice, tripService, database)) {
                break; // User chose to exit
            }
        }

    } catch (const std::exception& e) {
        std::cout << "❌ Error: " << e.what() << std::endl;
        std::cout << "Press Enter to continue...";
        std::cin.ignore();
        std::cin.get();
    }
}

void displayTripMenu() {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "           🗺️  TRIP PLANNING  🗺️" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "1. 🗼 Plan Paris Tour" << std::endl;
    std::cout << "2. 🇬🇧 Plan London Tour" << std::endl;
    std::cout << "3. 🗺️  Plan Custom Tour" << std::endl;
    std::cout << "4. 🇩🇪 Plan Berlin Tour" << std::endl;
    std::cout << "5. 📍 View Cities" << std::endl;
    std::cout << "0. 🔙 Back to Main Menu" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Enter choice (0-5): ";
}

bool handleTripChoice(int choice, TripService& tripService, DatabaseManager& database) {
    switch (choice) {
        case 1: {
            Trip trip = tripService.planParisTour();
            tripService.displayTrip(trip);
            waitForUser();
            return false;
        }
        case 2: {
            Trip trip = tripService.planLondonTour();
            tripService.displayTrip(trip);
            waitForUser();
            return false;
        }
        case 3: {
            Trip trip = tripService.planCustomTour();
            tripService.displayTrip(trip);
            waitForUser();
            return false;
        }
        case 4: {
            Trip trip = tripService.planBerlinTour();
            tripService.displayTrip(trip);
            waitForUser();
            return false;
        }
        case 5: {
            CityRepository cityRepo(database);
            CityService cityService(cityRepo);
            cityService.displayAllCities();
            waitForUser();
            return false;
        }
        case 0:
            return true; // Exit
        default:
            std::cout << "Invalid choice!" << std::endl;
            return false;
    }
}

void waitForUser() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}
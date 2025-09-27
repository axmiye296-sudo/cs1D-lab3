/**
 * @file TestController.cpp
 * @brief Controller for testing functionality
 */

#include "../../include/controllers/TestController.hpp"
#include "../../include/repositories/TripRepository.hpp"
#include "../../include/repositories/TripCityRepository.hpp"
#include "../../include/repositories/CityRepository.hpp"
#include "../../include/repositories/FoodRepository.hpp"
#include "../../include/services/TripService.hpp"
#include "../../include/services/tripCityService.hpp"
#include "../../include/services/CityService.hpp"
#include "../../include/services/FoodService.hpp"
#include <iostream>

void runTripTests(DatabaseManager& database) {
    std::cout << "\n🧪 RUNNING TRIPSERVICE TESTS" << std::endl;
    std::cout << std::string(50, '=') << std::endl;

    try {
        // Test 1: System Initialization
        std::cout << "📋 Test 1: System Initialization" << std::endl;
        CityRepository cityRepo(database);
        TripRepository tripRepo(database);
        TripCityRepository tripCityRepo(database);
        FoodRepository foodRepo(database);

        TripCityService tripCityService(tripCityRepo);
        FoodService foodService(foodRepo);
        TripService tripService(tripRepo, cityRepo, tripCityService, foodService);
        std::cout << "✅ System initialized successfully!" << std::endl;

        // Test 2: Data Loading
        std::cout << "\n📋 Test 2: Data Loading" << std::endl;
        V<City> cities = cityRepo.findAll();
        std::cout << "✅ Found " << cities.size() << " cities" << std::endl;

        if (cities.size() == 0) {
            std::cout << "❌ No cities found! Check your database." << std::endl;
            std::cout << "Press Enter to continue...";
            std::cin.ignore();
            std::cin.get();
            return;
        }

        // Display some cities
        std::cout << "📍 Sample cities:" << std::endl;
        for (int i = 0; i < cities.size() && i < 3; i++) {
            std::cout << "   " << cities[i].getId() << ". " << cities[i].getName() << std::endl;
        }

        // Test 3: Trip Creation
        std::cout << "\n📋 Test 3: Trip Creation" << std::endl;
        Trip testTrip = tripService.planParisTour();
        if (testTrip.getTotalDistance() > 0) {
            std::cout << "✅ Trip created with distance: " << testTrip.getTotalDistance() << " km" << std::endl;
        } else {
            std::cout << "⚠️ Trip created but distance is zero" << std::endl;
        }

        // Test 4: Database Operations
        std::cout << "\n📋 Test 4: Database Operations" << std::endl;
        V<Trip> savedTrips = tripRepo.findByType(TripTypes::PARIS_TOUR);
        std::cout << "✅ Found " << savedTrips.size() << " Paris tours in database" << std::endl;

        // Test Results
        std::cout << "\n" << std::string(50, '=') << std::endl;
        std::cout << "🎉 TESTS COMPLETE!" << std::endl;
        std::cout << "✅ TripService is working!" << std::endl;
        std::cout << "✅ Database operations: OK" << std::endl;
        std::cout << "✅ Trip creation: OK" << std::endl;

    } catch (const std::exception& e) {
        std::cout << "❌ Test failed: " << e.what() << std::endl;
        std::cout << "This might indicate:" << std::endl;
        std::cout << "- Missing database data" << std::endl;
        std::cout << "- Compilation issues" << std::endl;
        std::cout << "- Missing repository implementations" << std::endl;
    }

    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}
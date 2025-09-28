#include <crow.h>
#include "../routes/cityRoutes.cpp"
#include "../routes/tripRoutes.cpp"  // ✅ Add this line
#include "../../include/services/CityService.hpp"
#include "../../include/services/FoodService.hpp"
#include "../../include/services/TripService.hpp"  // ✅ Add this line
#include "../../include/services/tripCityService.hpp"  // ✅ Add this line
#include "../../include/repositories/CityRepository.hpp"
#include "../../include/repositories/FoodRepository.hpp"
#include "../../include/repositories/TripRepository.hpp"  // ✅ Add this line
#include "../../include/repositories/TripCityRepository.hpp"  // ✅ Add this line
#include "../../include/databaseManager.hpp"
#include <iostream>

void startApiServer() {
    crow::SimpleApp app;
    const int port = 3001;

    // Initialize database and services
    DatabaseManager& database = DatabaseManager::getInstance();
    if (!database.connect()) {
        std::cerr << "Failed to connect to database!" << std::endl;
        return;
    }

    // Initialize repositories
    CityRepository cityRepo(database);
    FoodRepository foodRepo(database);
    TripRepository tripRepo(database);  // ✅ Add this line
    TripCityRepository tripCityRepo(database);  // ✅ Add this line

    // Initialize services
    CityService cityService(cityRepo);
    FoodService foodService(foodRepo);
    TripCityService tripCityService(tripCityRepo);  // ✅ Add this line
    TripService tripService(tripRepo, cityRepo, tripCityService, foodService);  // ✅ Add this line

    // Register all routes
    registerCityRoutes(app, cityService, foodService);
    registerTripRoutes(app, tripService, cityService, tripCityService);  // ✅ Add this line

    // Simple test route
    CROW_ROUTE(app, "/")([]() {
        return "Trip Planning API is running";
    });

    CROW_ROUTE(app, "/health")([](){
        return crow::response(200, "OK");
    });

    std::cout << "Starting Trip Planning API server on port " << port << std::endl;
    std::cout << "Available endpoints:" << std::endl;
    std::cout << "  GET /api/cities - Get all cities" << std::endl;
    std::cout << "  GET /api/cities/food - Get all cities with their foods" << std::endl;
    std::cout << "  GET /api/cities/{id}/food - Get foods for a specific city" << std::endl;
    std::cout << "  GET /api/trips/paris - Plan Paris tour (all cities)" << std::endl;  // ✅ Add this line
    std::cout << "  GET /api/trips/london - Plan London tour" << std::endl;  // ✅ Add this line
    std::cout << "  GET /api/trips/custom - Plan custom tour" << std::endl;  // ✅ Add this line
    std::cout << "  GET /api/trips/berlin - Plan Berlin tour" << std::endl;  // ✅ Add this line
    std::cout << "  GET /api/trips/{id} - Get trip details by ID" << std::endl;  // ✅ Add this line
    std::cout << "  GET /health - Health check" << std::endl;

    app.port(port).run();
}
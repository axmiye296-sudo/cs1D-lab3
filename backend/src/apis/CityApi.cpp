#include <crow.h>
#include "../../include/routes/cityRoutes.hpp"
#include "../../include/routes/tripRoutes.hpp"
#include "../../include/services/CityService.hpp"
#include "../../include/services/FoodService.hpp"
#include "../../include/services/TripService.hpp"
#include "../../include/services/tripCityService.hpp"
#include "../../include/repositories/CityRepository.hpp"
#include "../../include/repositories/FoodRepository.hpp"
#include "../../include/repositories/TripRepository.hpp"
#include "../../include/repositories/TripCityRepository.hpp"
#include "../../include/repositories/CityDistanceRepository.hpp"
#include "../../include/databaseManager.hpp"
#include <iostream>

void startApiServer() {
    crow::SimpleApp app;

    // Initialize database using singleton pattern
    DatabaseManager& database = DatabaseManager::getInstance();

    // Connect to database./m

    if (!database.connect()) {
        std::cerr << "❌ Failed to connect to database!" << std::endl;
        return;
    }

    // Initialize repositories
    CityRepository cityRepo(database);
    FoodRepository foodRepo(database);
    TripRepository tripRepo(database);
    TripCityRepository tripCityRepo(database);
    CityDistanceRepository cityDistanceRepo(database);

    // Initialize services
    CityService cityService(cityRepo);
    FoodService foodService(foodRepo);
    TripCityService tripCityService(tripCityRepo);
    TripService tripService(tripRepo, cityDistanceRepo, tripCityService);

    // Register all routes
    registerCityRoutes(app, cityService, foodService, cityDistanceRepo);
    registerTripRoutes(app, tripService, cityService, tripCityService);

    // Simple test route
    CROW_ROUTE(app, "/")([]() {
        return "Trip Planning API is running";
    });

    // Start server
    std::cout << "🚀 Starting Trip Planning API Server..." << std::endl;
    std::cout << "📍 Available endpoints:" << std::endl;
    std::cout << "  GET / - API status" << std::endl;
    std::cout << "  GET /api/cities - Get all cities" << std::endl;
    std::cout << "  GET /api/cities/distances - Get all city distances" << std::endl;
    std::cout << "  GET /api/cities/food - Get all cities with food" << std::endl;
    std::cout << "  GET /api/cities/{id}/food - Get foods for city" << std::endl;
    std::cout << "  GET /api/trips/paris - Plan Paris tour (all cities)" << std::endl;
    std::cout << "  GET /api/trips/london - Plan London tour" << std::endl;
    std::cout << "  GET /api/trips/custom - Plan custom tour" << std::endl;
    std::cout << "  GET /api/trips/berlin - Plan Berlin tour" << std::endl;
    std::cout << "  GET /api/trips/{id} - Get trip by ID" << std::endl;
    std::cout << "🌐 Server running on http://localhost:3001" << std::endl;

    app.port(3001).run();
}

int main() {
    std::cout << "🚀 Trip Planning API Server Starting..." << std::endl;
    startApiServer();
   return 0;
}
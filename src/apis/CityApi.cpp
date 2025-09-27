#include <crow.h>
#include "../routes/cityRoutes.cpp"
#include "../../include/services/CityService.hpp"
#include "../../include/services/FoodService.hpp"
#include "../../include/repositories/CityRepository.hpp"
#include "../../include/repositories/FoodRepository.hpp"
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
    
    // Initialize repositories and services
    CityRepository cityRepo(database);
    FoodRepository foodRepo(database);
    CityService cityService(cityRepo);
    FoodService foodService(foodRepo);
    
    // Register all routes with both services
    registerCityRoutes(app, cityService, foodService);
    
    // Simple test route
    CROW_ROUTE(app, "/")([]() {
        return "API is running";
    });

    CROW_ROUTE(app, "/health")([](){
        return crow::response(200, "OK");
    });

    std::cout << "Starting API server on port " << port << std::endl;
    std::cout << "Available endpoints:" << std::endl;
    std::cout << "  GET /api/cities - Get all cities" << std::endl;
    std::cout << "  GET /api/cities/food - Get all cities with their foods" << std::endl;
    std::cout << "  GET /api/cities/{id}/food - Get foods for a specific city" << std::endl;
    std::cout << "  GET /health - Health check" << std::endl;

    app.port(port).run();
}

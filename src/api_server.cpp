/**
 * @file api_server.cpp
 * @brief REST API server for CS1D Lab 3 Trip Planning Application
 * @author CS1D Lab 3 Team
 * @date 2025
 * 
 * This file contains the REST API server implementation using Crow framework.
 * It provides HTTP endpoints to access the SQLite database for trip planning data.
 *
 * Made this file because it allowed me to run the API
 */

#include <crow.h>
#include "../include/header.hpp"
#include "../include/databaseManager.hpp"
#include "../include/services/CityService.hpp"
#include "../include/services/FoodService.hpp"
#include "../include/services/tripCityService.hpp"
#include "../include/repositories/CityRepository.hpp"
#include "../include/repositories/FoodRepository.hpp"
#include "../include/repositories/TripCityRepository.hpp"
#include <json/json.h>

/**
 * @brief Convert vector of cities to JSON format
 * @param cities Vector of City objects
 * @return Json::Value JSON array of cities
 */
Json::Value citiesToJson(const V<City>& cities) {
    Json::Value jsonArray(Json::arrayValue);
    for (const auto& city : cities) {
        Json::Value cityJson;
        cityJson["id"] = city.getId();
        cityJson["name"] = city.getName();
        jsonArray.append(cityJson);
    }
    return jsonArray;
}

/**
 * @brief Convert vector of foods to JSON format
 * @param foods Vector of Food objects
 * @return Json::Value JSON array of foods
 */
Json::Value foodsToJson(const V<Food>& foods) {
    Json::Value jsonArray(Json::arrayValue);
    for (const auto& food : foods) {
        Json::Value foodJson;
        foodJson["id"] = food.getId();
        foodJson["name"] = food.getName();
        foodJson["city_id"] = food.getCityId();
        foodJson["price"] = food.getPrice();
        jsonArray.append(foodJson);
    }
    return jsonArray;
}

/**
 * @brief Main function for the REST API server
 * @return int Exit status code
 * 
 * Sets up and runs the Crow web server with various API endpoints:
 * - GET /api/cities - Get all cities
 * - GET /api/foods - Get all foods
 * - GET /api/cities/<id>/foods - Get foods for a specific city
 * - GET /health - Health check endpoint
 */
int main() {
    // Initialize database
    DatabaseManager& database = DatabaseManager::getInstance();
    
    if (!database.connect()) {
        std::cerr << "Failed to connect to database!" << std::endl;
        return 1;
    }

    // Initialize repositories and services
    CityRepository cityRepo(database);
    FoodRepository foodRepo(database);
    TripCityRepository tripCityRepo(database);
    
    CityService cityService(cityRepo);
    FoodService foodService(foodRepo);
    TripCityService tripCityService(tripCityRepo);

    // Create Crow app
    crow::SimpleApp app;

    // Enable CORS for web frontend
    // Note: compression may not be available in this Crow version

    // Health check endpoint
    CROW_ROUTE(app, "/health")
    ([]{
        Json::Value response;
        response["status"] = "healthy";
        response["message"] = "CS1D Lab 3 API Server is running";
        response["timestamp"] = std::time(nullptr);
        
        Json::StreamWriterBuilder builder;
        std::string jsonString = Json::writeString(builder, response);
        
        auto res = crow::response(200);
        res.add_header("Content-Type", "application/json");
        res.add_header("Access-Control-Allow-Origin", "*");
        res.body = jsonString;
        return res;
    });

    // Get all cities
    CROW_ROUTE(app, "/api/cities").methods(crow::HTTPMethod::GET)
    ([&cityService](const crow::request& req) {
        try {
            V<City> cities = cityService.getAllCities();
            Json::Value response = citiesToJson(cities);
            
            Json::StreamWriterBuilder builder;
            std::string jsonString = Json::writeString(builder, response);
            
            auto res = crow::response(200);
            res.add_header("Content-Type", "application/json");
            res.add_header("Access-Control-Allow-Origin", "*");
            res.body = jsonString;
            return res;
        } catch (const std::exception& e) {
            Json::Value error;
            error["error"] = e.what();
            
            Json::StreamWriterBuilder builder;
            std::string jsonString = Json::writeString(builder, error);
            
            auto res = crow::response(500);
            res.add_header("Content-Type", "application/json");
            res.add_header("Access-Control-Allow-Origin", "*");
            res.body = jsonString;
            return res;
        }
    });

    // Get all foods
    CROW_ROUTE(app, "/api/foods").methods(crow::HTTPMethod::GET)
    ([&foodService](const crow::request& req) {
        try {
            V<Food> foods = foodService.getAllFoods();
            Json::Value response = foodsToJson(foods);
            
            Json::StreamWriterBuilder builder;
            std::string jsonString = Json::writeString(builder, response);
            
            auto res = crow::response(200);
            res.add_header("Content-Type", "application/json");
            res.add_header("Access-Control-Allow-Origin", "*");
            res.body = jsonString;
            return res;
        } catch (const std::exception& e) {
            Json::Value error;
            error["error"] = e.what();
            
            Json::StreamWriterBuilder builder;
            std::string jsonString = Json::writeString(builder, error);
            
            auto res = crow::response(500);
            res.add_header("Content-Type", "application/json");
            res.add_header("Access-Control-Allow-Origin", "*");
            res.body = jsonString;
            return res;
        }
    });

    // Get foods for a specific city
    CROW_ROUTE(app, "/api/cities/<int>/foods").methods(crow::HTTPMethod::GET)
    ([&foodService](const crow::request& req, int cityId) {
        try {
            V<Food> foods = foodService.getFoodsByCityId(cityId);
            Json::Value response = foodsToJson(foods);
            
            Json::StreamWriterBuilder builder;
            std::string jsonString = Json::writeString(builder, response);
            
            auto res = crow::response(200);
            res.add_header("Content-Type", "application/json");
            res.add_header("Access-Control-Allow-Origin", "*");
            res.body = jsonString;
            return res;
        } catch (const std::exception& e) {
            Json::Value error;
            error["error"] = e.what();
            
            Json::StreamWriterBuilder builder;
            std::string jsonString = Json::writeString(builder, error);
            
            auto res = crow::response(500);
            res.add_header("Content-Type", "application/json");
            res.add_header("Access-Control-Allow-Origin", "*");
            res.body = jsonString;
            return res;
        }
    });

    // Get a specific city by ID
    CROW_ROUTE(app, "/api/cities/<int>").methods(crow::HTTPMethod::GET)
    ([&cityService](const crow::request& req, int cityId) {
        try {
            // Get city by ID - using getAllCities and filtering
            V<City> allCities = cityService.getAllCities();
            City* foundCity = nullptr;
            for (auto& city : allCities) {
                if (city.getId() == cityId) {
                    foundCity = &city;
                    break;
                }
            }
            
            if (foundCity) {
                Json::Value response;
                response["id"] = foundCity->getId();
                response["name"] = foundCity->getName();
                
                Json::StreamWriterBuilder builder;
                std::string jsonString = Json::writeString(builder, response);
                
                auto res = crow::response(200);
                res.add_header("Content-Type", "application/json");
                res.add_header("Access-Control-Allow-Origin", "*");
                res.body = jsonString;
                return res;
            } else {
                Json::Value error;
                error["error"] = "City not found";
                
                Json::StreamWriterBuilder builder;
                std::string jsonString = Json::writeString(builder, error);
                
                auto res = crow::response(404);
                res.add_header("Content-Type", "application/json");
                res.add_header("Access-Control-Allow-Origin", "*");
                res.body = jsonString;
                return res;
            }
        } catch (const std::exception& e) {
            Json::Value error;
            error["error"] = e.what();
            
            Json::StreamWriterBuilder builder;
            std::string jsonString = Json::writeString(builder, error);
            
            auto res = crow::response(500);
            res.add_header("Content-Type", "application/json");
            res.add_header("Access-Control-Allow-Origin", "*");
            res.body = jsonString;
            return res;
        }
    });

    // Start the server
    std::cout << "🚀 Starting CS1D Lab 3 API Server..." << std::endl;
    std::cout << "🌐 Server running on http://localhost:3001" << std::endl;
    std::cout << "📚 Available endpoints:" << std::endl;
    std::cout << "  GET /health - Health check" << std::endl;
    std::cout << "  GET /api/cities - Get all cities" << std::endl;
    std::cout << "  GET /api/cities/<id> - Get specific city" << std::endl;
    std::cout << "  GET /api/foods - Get all foods" << std::endl;
    std::cout << "  GET /api/cities/<id>/foods - Get foods for city" << std::endl;
    std::cout << "🛑 Press Ctrl+C to stop the server" << std::endl;

    // Run server on port 3001
    app.port(3001).multithreaded().run();

    // Cleanup
    database.disconnect();
    return 0;
}
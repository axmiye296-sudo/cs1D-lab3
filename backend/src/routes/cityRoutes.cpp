/**
 * @file cityRoutes.cpp
 * @brief Implementation of city-related API routes
 */

#include "crow/crow_all.h"
#include "../../include/entities/City.hpp"
#include "../../include/entities/CityDistance.hpp"
#include "../../include/services/CityService.hpp"
#include "../../include/services/FoodService.hpp"
#include "../../include/repositories/CityDistanceRepository.hpp"

/**
 * @brief Register city-related API routes
 * @param app Reference to Crow SimpleApp instance
 * @param cityService Reference to CityService for city operations
 * @param foodService Reference to FoodService for food operations
 * @param cityDistanceRepo Reference to CityDistanceRepository for distance operations
 * 
 * Registers all city-related API endpoints including:
 * - GET /api/cities - Retrieve all cities
 * - GET /api/cities/distances - Retrieve all city distances
 * - GET /api/cities/{id}/foods - Retrieve foods for a specific city
 * - GET /api/cities/{id}/distances - Retrieve distances from a specific city
 */
void registerCityRoutes(crow::SimpleApp& app, CityService& cityService, FoodService& foodService, CityDistanceRepository& cityDistanceRepo) {
    // ============================================================================
    // CITY ROUTES
    // ============================================================================

    /**
     * @brief GET /api/cities - Retrieve all cities
     * 
     * Returns a JSON response containing all cities from the database.
     * Response format: {"cities": [{"id": 1, "name": "Paris"}, ...], "count": 5}
     */
    CROW_ROUTE(app, "/api/cities").methods("GET"_method)([&cityService]() {
        // Fetch cities directly from your existing database
        V<City> cities = cityService.getAllCities();

        // Create JSON response using Crow's built-in support
        crow::json::wvalue result;
        result["cities"] = crow::json::wvalue::list();

        for (size_t i = 0; i < cities.size(); i++) {
            result["cities"][i]["id"] = cities[i].getId();
            result["cities"][i]["name"] = cities[i].getName();
        }

        result["count"] = (int)cities.size();

        return crow::response(200, result);
    });

    /**
     * @brief GET /api/cities/distances - Retrieve all city distances
     * 
     * Returns a JSON response containing all city distance relationships.
     * Response format: {"distances": [{"from_city_id": 1, "to_city_id": 2, "distance": 100}, ...], "count": 10}
     */
    CROW_ROUTE(app, "/api/cities/distances").methods("GET"_method)([&cityDistanceRepo]() {
        try {
            std::cout << "🔍 API: Fetching all city distances..." << std::endl;
            
            // Fetch all distances from the database
            V<CityDistance> distances = cityDistanceRepo.findAll();
            
            std::cout << "📊 API: Found " << distances.size() << " distance records" << std::endl;

            // Create JSON response
            crow::json::wvalue result;
            result["distances"] = crow::json::wvalue::list();

            for (size_t i = 0; i < distances.size(); i++) {
                result["distances"][i]["from_city_id"] = distances[i].getFromCityId();
                result["distances"][i]["to_city_id"] = distances[i].getToCityId();
                result["distances"][i]["distance"] = distances[i].getDistance();
            }

            result["count"] = (int)distances.size();
            result["message"] = "All city distances retrieved successfully";

            return crow::response(200, result);
        } catch (const std::exception& e) {
            std::cout << "❌ API Error fetching distances: " << e.what() << std::endl;
            crow::json::wvalue error;
            error["error"] = "Failed to fetch city distances";
            error["details"] = e.what();
            return crow::response(500, error);
        }
    });

    // GET /api/cities/food - Get all cities with their corresponding food
    CROW_ROUTE(app, "/api/cities/food").methods("GET"_method)([&cityService, &foodService]() {
        // Fetch cities directly from your existing database
        V<City> cities = cityService.getAllCities();

        // Create JSON response using Crow's built-in support
        crow::json::wvalue result;
        result["cities"] = crow::json::wvalue::list();

        for (size_t i = 0; i < cities.size(); i++) {
            result["cities"][i]["id"] = cities[i].getId();
            result["cities"][i]["name"] = cities[i].getName();
            
            // Get foods for this city
            V<Food> foods = foodService.getFoodsByCityId(cities[i].getId());
            result["cities"][i]["foods"] = crow::json::wvalue::list();
            
            for (size_t j = 0; j < foods.size(); j++) {
                result["cities"][i]["foods"][j]["id"] = foods[j].getId();
                result["cities"][i]["foods"][j]["name"] = foods[j].getName();
                result["cities"][i]["foods"][j]["price"] = foods[j].getPrice();
            }
        }

        result["count"] = (int)cities.size();

        return crow::response(200, result);
    });

    // GET /api/cities/{id}/food - Get foods for a specific city
    CROW_ROUTE(app, "/api/cities/<int>/food").methods("GET"_method)([&cityService, &foodService](int cityId) {
        try {
            // Get the city first to validate it exists
            V<City> cities = cityService.getAllCities();
            bool cityExists = false;
            std::string cityName;
            
            for (const auto& city : cities) {
                if (city.getId() == cityId) {
                    cityExists = true;
                    cityName = city.getName();
                    break;
                }
            }
            
            if (!cityExists) {
                crow::json::wvalue error;
                error["error"] = "City not found";
                error["city_id"] = cityId;
                return crow::response(404, error);
            }
            
            // Get food for this specific city
            V<Food> food = foodService.getFoodsByCityId(cityId);
            
            // Create JSON response
            crow::json::wvalue result;
            result["city_id"] = cityId;
            result["city_name"] = cityName;
            result["food"] = crow::json::wvalue::list();
            
            for (size_t i = 0; i < food.size(); i++) {
                result["food"][i]["id"] = food[i].getId();
                result["food"][i]["name"] = food[i].getName();
                result["food"][i]["price"] = food[i].getPrice();
            }
            
            result["count"] = (int)food.size();
            
            return crow::response(200, result);
        } catch (const std::exception& e) {
            crow::json::wvalue error;
            error["error"] = "Failed to fetch foods for city";
            return crow::response(500, error);
        }
    });

    // Might not need - was trying to figure out how to display city distances in custom trip frontend
    // GET /api/cities/with-distances - Get cities with distances from previous city
    CROW_ROUTE(app, "/api/cities/with-distances").methods("GET"_method)([&cityService, &cityDistanceRepo]() {
        try {
            // Fetch all cities
            V<City> cities = cityService.getAllCities();
            
            // Create JSON response
            crow::json::wvalue result;
            result["cities"] = crow::json::wvalue::list();

            for (size_t i = 0; i < cities.size(); i++) {
                result["cities"][i]["id"] = cities[i].getId();
                result["cities"][i]["name"] = cities[i].getName();
                
                // Calculate distance from previous city (if not first city)
                if (i > 0) {
                    int prevCityId = cities[i-1].getId();
                    int currentCityId = cities[i].getId();
                    
                    // Find distance between previous city and current city
                    V<CityDistance> allDistances = cityDistanceRepo.findAll();
                    int distanceFromPrev = -1;
                    
                    for (const auto& dist : allDistances) {
                        if ((dist.getFromCityId() == prevCityId && dist.getToCityId() == currentCityId) ||
                            (dist.getFromCityId() == currentCityId && dist.getToCityId() == prevCityId)) {
                            distanceFromPrev = dist.getDistance();
                            break;
                        }
                    }
                    
                    result["cities"][i]["distance_from_previous"] = distanceFromPrev;
                    result["cities"][i]["previous_city"] = cities[i-1].getName();
                } else {
                    result["cities"][i]["distance_from_previous"] = 0;
                    result["cities"][i]["previous_city"] = "Starting point";
                }
            }

            result["count"] = (int)cities.size();
            result["message"] = "Cities with distances from previous city";

            return crow::response(200, result);
        } catch (const std::exception& e) {
            crow::json::wvalue error;
            error["error"] = "Failed to fetch cities with distances";
            error["details"] = e.what();
            return crow::response(500, error);
        }
    });
}
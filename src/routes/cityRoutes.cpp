#include <crow.h>
#include "../../include/entities/City.hpp"
#include "../../include/services/CityService.hpp"
#include "../../include/services/FoodService.hpp"

void registerCityRoutes(crow::SimpleApp& app, CityService& cityService, FoodService& foodService) {
    // GET /api/cities - Get all cities from database
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
}
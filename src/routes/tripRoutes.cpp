#include <crow.h>
#include "../../include/entities/Trip.hpp"
#include "../../include/entities/City.hpp"
#include "../../include/services/TripService.hpp"
#include "../../include/services/CityService.hpp"
#include "../../include/services/tripCityService.hpp"

void registerTripRoutes(crow::SimpleApp& app, TripService& tripService, CityService& cityService, TripCityService& tripCityService) {
    
    // GET /api/trips/paris - Plan and return Paris tour
    CROW_ROUTE(app, "/api/trips/paris").methods("GET"_method)([&tripService, &cityService, &tripCityService]() {
        try {
            // Plan the Paris tour
            Trip parisTrip = tripService.planParisTour();
            
            if (parisTrip.getId() == 0) {
                crow::json::wvalue error;
                error["error"] = "Failed to create Paris tour";
                error["message"] = "Not enough cities in database or trip creation failed";
                return crow::response(400, error);
            }
            
            // Get all cities for name lookup
            V<City> allCities = cityService.getAllCities();
            
            // Get cities in the trip
            V<TripCity> tripCities = tripCityService.getCitiesForTrip(parisTrip.getId());
            
            // Create JSON response
            crow::json::wvalue result;
            result["trip"]["id"] = parisTrip.getId();
            result["trip"]["type"] = parisTrip.getTripType();
            result["trip"]["start_city_id"] = parisTrip.getStartCityId();
            result["trip"]["total_distance"] = parisTrip.getTotalDistance();
            
            // Find start city name
            std::string startCityName = "Unknown";
            for (const auto& city : allCities) {
                if (city.getId() == parisTrip.getStartCityId()) {
                    startCityName = city.getName();
                    break;
                }
            }
            result["trip"]["start_city_name"] = startCityName;
            
            // Add cities in route
            result["trip"]["cities"] = crow::json::wvalue::list();
            
            // Sort trip cities by visit order
            std::sort(tripCities.begin(), tripCities.end(), 
                      [](const TripCity& a, const TripCity& b) {
                          return a.getVisitOrder() < b.getVisitOrder();
                      });
            
            for (size_t i = 0; i < tripCities.size(); i++) {
                // Find city name
                std::string cityName = "Unknown";
                for (const auto& city : allCities) {
                    if (city.getId() == tripCities[i].getCityId()) {
                        cityName = city.getName();
                        break;
                    }
                }
                
                result["trip"]["cities"][i]["city_id"] = tripCities[i].getCityId();
                result["trip"]["cities"][i]["city_name"] = cityName;
                result["trip"]["cities"][i]["visit_order"] = tripCities[i].getVisitOrder();
            }
            
            result["trip"]["total_cities"] = (int)tripCities.size();
            result["success"] = true;
            result["message"] = "Paris tour created successfully";
            
            return crow::response(200, result);
            
        } catch (const std::exception& e) {
            crow::json::wvalue error;
            error["error"] = "Failed to create Paris tour";
            error["message"] = e.what();
            return crow::response(500, error);
        }
    });
    
    // GET /api/trips/london - Plan and return London tour
    CROW_ROUTE(app, "/api/trips/london").methods("GET"_method)([&tripService, &cityService, &tripCityService]() {
        try {
            Trip londonTrip = tripService.planLondonTour();
            
            if (londonTrip.getId() == 0) {
                crow::json::wvalue error;
                error["error"] = "Failed to create London tour";
                return crow::response(400, error);
            }
            
            // Get all cities for name lookup
            V<City> allCities = cityService.getAllCities();
            V<TripCity> tripCities = tripCityService.getCitiesForTrip(londonTrip.getId());
            
            // Create JSON response (same structure as Paris tour)
            crow::json::wvalue result;
            result["trip"]["id"] = londonTrip.getId();
            result["trip"]["type"] = londonTrip.getTripType();
            result["trip"]["start_city_id"] = londonTrip.getStartCityId();
            result["trip"]["total_distance"] = londonTrip.getTotalDistance();
            
            // Find start city name
            std::string startCityName = "Unknown";
            for (const auto& city : allCities) {
                if (city.getId() == londonTrip.getStartCityId()) {
                    startCityName = city.getName();
                    break;
                }
            }
            result["trip"]["start_city_name"] = startCityName;
            
            // Add cities in route
            result["trip"]["cities"] = crow::json::wvalue::list();
            std::sort(tripCities.begin(), tripCities.end(), 
                      [](const TripCity& a, const TripCity& b) {
                          return a.getVisitOrder() < b.getVisitOrder();
                      });
            
            for (size_t i = 0; i < tripCities.size(); i++) {
                std::string cityName = "Unknown";
                for (const auto& city : allCities) {
                    if (city.getId() == tripCities[i].getCityId()) {
                        cityName = city.getName();
                        break;
                    }
                }
                
                result["trip"]["cities"][i]["city_id"] = tripCities[i].getCityId();
                result["trip"]["cities"][i]["city_name"] = cityName;
                result["trip"]["cities"][i]["visit_order"] = tripCities[i].getVisitOrder();
            }
            
            result["trip"]["total_cities"] = (int)tripCities.size();
            result["success"] = true;
            result["message"] = "London tour created successfully";
            
            return crow::response(200, result);
            
        } catch (const std::exception& e) {
            crow::json::wvalue error;
            error["error"] = "Failed to create London tour";
            error["message"] = e.what();
            return crow::response(500, error);
        }
    });
    
    // GET /api/trips/custom - Plan and return custom tour
    CROW_ROUTE(app, "/api/trips/custom").methods("GET"_method)([&tripService, &cityService, &tripCityService]() {
        try {
            Trip customTrip = tripService.planCustomTour();
            
            if (customTrip.getId() == 0) {
                crow::json::wvalue error;
                error["error"] = "Failed to create custom tour";
                return crow::response(400, error);
            }
            
            // Get all cities for name lookup
            V<City> allCities = cityService.getAllCities();
            V<TripCity> tripCities = tripCityService.getCitiesForTrip(customTrip.getId());
            
            // Create JSON response (same structure)
            crow::json::wvalue result;
            result["trip"]["id"] = customTrip.getId();
            result["trip"]["type"] = customTrip.getTripType();
            result["trip"]["start_city_id"] = customTrip.getStartCityId();
            result["trip"]["total_distance"] = customTrip.getTotalDistance();
            
            // Find start city name
            std::string startCityName = "Unknown";
            for (const auto& city : allCities) {
                if (city.getId() == customTrip.getStartCityId()) {
                    startCityName = city.getName();
                    break;
                }
            }
            result["trip"]["start_city_name"] = startCityName;
            
            // Add cities in route
            result["trip"]["cities"] = crow::json::wvalue::list();
            std::sort(tripCities.begin(), tripCities.end(), 
                      [](const TripCity& a, const TripCity& b) {
                          return a.getVisitOrder() < b.getVisitOrder();
                      });
            
            for (size_t i = 0; i < tripCities.size(); i++) {
                std::string cityName = "Unknown";
                for (const auto& city : allCities) {
                    if (city.getId() == tripCities[i].getCityId()) {
                        cityName = city.getName();
                        break;
                    }
                }
                
                result["trip"]["cities"][i]["city_id"] = tripCities[i].getCityId();
                result["trip"]["cities"][i]["city_name"] = cityName;
                result["trip"]["cities"][i]["visit_order"] = tripCities[i].getVisitOrder();
            }
            
            result["trip"]["total_cities"] = (int)tripCities.size();
            result["success"] = true;
            result["message"] = "Custom tour created successfully";
            
            return crow::response(200, result);
            
        } catch (const std::exception& e) {
            crow::json::wvalue error;
            error["error"] = "Failed to create custom tour";
            error["message"] = e.what();
            return crow::response(500, error);
        }
    });
    
    // GET /api/trips/berlin - Plan and return Berlin tour
    CROW_ROUTE(app, "/api/trips/berlin").methods("GET"_method)([&tripService, &cityService, &tripCityService]() {
        try {
            Trip berlinTrip = tripService.planBerlinTour();
            
            if (berlinTrip.getId() == 0) {
                crow::json::wvalue error;
                error["error"] = "Failed to create Berlin tour";
                return crow::response(400, error);
            }
            
            // Get all cities for name lookup
            V<City> allCities = cityService.getAllCities();
            V<TripCity> tripCities = tripCityService.getCitiesForTrip(berlinTrip.getId());
            
            // Create JSON response (same structure)
            crow::json::wvalue result;
            result["trip"]["id"] = berlinTrip.getId();
            result["trip"]["type"] = berlinTrip.getTripType();
            result["trip"]["start_city_id"] = berlinTrip.getStartCityId();
            result["trip"]["total_distance"] = berlinTrip.getTotalDistance();
            
            // Find start city name
            std::string startCityName = "Unknown";
            for (const auto& city : allCities) {
                if (city.getId() == berlinTrip.getStartCityId()) {
                    startCityName = city.getName();
                    break;
                }
            }
            result["trip"]["start_city_name"] = startCityName;
            
            // Add cities in route
            result["trip"]["cities"] = crow::json::wvalue::list();
            std::sort(tripCities.begin(), tripCities.end(), 
                      [](const TripCity& a, const TripCity& b) {
                          return a.getVisitOrder() < b.getVisitOrder();
                      });
            
            for (size_t i = 0; i < tripCities.size(); i++) {
                std::string cityName = "Unknown";
                for (const auto& city : allCities) {
                    if (city.getId() == tripCities[i].getCityId()) {
                        cityName = city.getName();
                        break;
                    }
                }
                
                result["trip"]["cities"][i]["city_id"] = tripCities[i].getCityId();
                result["trip"]["cities"][i]["city_name"] = cityName;
                result["trip"]["cities"][i]["visit_order"] = tripCities[i].getVisitOrder();
            }
            
            result["trip"]["total_cities"] = (int)tripCities.size();
            result["success"] = true;
            result["message"] = "Berlin tour created successfully";
            
            return crow::response(200, result);
            
        } catch (const std::exception& e) {
            crow::json::wvalue error;
            error["error"] = "Failed to create Berlin tour";
            error["message"] = e.what();
            return crow::response(500, error);
        }
    });
    
    // GET /api/trips/{id} - Get details of a specific trip
    CROW_ROUTE(app, "/api/trips/<int>").methods("GET"_method)([&cityService, &tripCityService](int tripId) {
        try {
            // Get cities in the trip
            V<TripCity> tripCities = tripCityService.getCitiesForTrip(tripId);
            
            if (tripCities.empty()) {
                crow::json::wvalue error;
                error["error"] = "Trip not found or has no cities";
                error["trip_id"] = tripId;
                return crow::response(404, error);
            }
            
            // Get all cities for name lookup
            V<City> allCities = cityService.getAllCities();
            
            // Create JSON response
            crow::json::wvalue result;
            result["trip_id"] = tripId;
            result["cities"] = crow::json::wvalue::list();
            
            // Sort by visit order
            std::sort(tripCities.begin(), tripCities.end(), 
                      [](const TripCity& a, const TripCity& b) {
                          return a.getVisitOrder() < b.getVisitOrder();
                      });
            
            for (size_t i = 0; i < tripCities.size(); i++) {
                std::string cityName = "Unknown";
                for (const auto& city : allCities) {
                    if (city.getId() == tripCities[i].getCityId()) {
                        cityName = city.getName();
                        break;
                    }
                }
                
                result["cities"][i]["city_id"] = tripCities[i].getCityId();
                result["cities"][i]["city_name"] = cityName;
                result["cities"][i]["visit_order"] = tripCities[i].getVisitOrder();
            }
            
            result["total_cities"] = (int)tripCities.size();
            result["success"] = true;
            
            return crow::response(200, result);
            
        } catch (const std::exception& e) {
            crow::json::wvalue error;
            error["error"] = "Failed to fetch trip details";
            error["message"] = e.what();
            return crow::response(500, error);
        }
    });
}
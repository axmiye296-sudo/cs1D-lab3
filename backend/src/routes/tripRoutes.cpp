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
            double debugDistance = parisTrip.getTotalDistance();
            std::cout << "🔍 API DEBUG: Trip ID = " << parisTrip.getId() << std::endl;
            std::cout << "🔍 API DEBUG: Trip distance = " << debugDistance << std::endl;
            std::cout << "🔍 API DEBUG: Trip type = " << parisTrip.getTripType() << std::endl;

            // Add distance in multiple formats to ensure frontend can find it
            result["trip"]["distance"] = debugDistance;           // Alternative name
            result["distance"] = debugDistance;                   // Root level
            result["totalDistance"] = debugDistance;              // Root level camelCase
            result["trip"]["totalDistance"] = debugDistance;      // Trip level camelCase

            // Add as string in case there's a number parsing issue
            result["trip"]["distance_string"] = std::to_string((int)debugDistance) + " km";
            result["distance_string"] = std::to_string((int)debugDistance) + " km";
            
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
    CROW_ROUTE(app, "/api/trips/london").methods("GET"_method)([&tripService, &cityService, &tripCityService](const crow::request& req) {
        try {
            // ✅ NEW: Parse the 'cities' query parameter
            int numCities = 13; // Default to all cities
            auto citiesParam = req.url_params.get("cities");
            if (citiesParam) {
                try {
                    numCities = std::stoi(citiesParam);
                    std::cout << "🔍 London tour requested with " << numCities << " cities" << std::endl;
                } catch (const std::exception& e) {
                    std::cout << "⚠️ Invalid cities parameter, using default (13)" << std::endl;
                    numCities = 13;
                }
            }
            
            // ✅ UPDATED: Pass numCities to the service
            Trip londonTrip = tripService.planLondonTour(numCities);
            
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


// ✅ ADD THESE DEBUG LINES (same as Paris tour):
            double debugDistance = londonTrip.getTotalDistance();
            std::cout << "🔍 API DEBUG: London Trip ID = " << londonTrip.getId() << std::endl;
            std::cout << "🔍 API DEBUG: London Trip distance = " << debugDistance << std::endl;
            std::cout << "🔍 API DEBUG: London Trip type = " << londonTrip.getTripType() << std::endl;

            // Add distance in multiple formats to ensure frontend can find it
            result["trip"]["distance"] = debugDistance;           // Alternative name
            result["distance"] = debugDistance;                   // Root level
            result["totalDistance"] = debugDistance;              // Root level camelCase
            result["trip"]["totalDistance"] = debugDistance;      // Trip level camelCase

            // Add as string in case there's a number parsing issue
            result["trip"]["distance_string"] = std::to_string((int)debugDistance) + " km";
            result["distance_string"] = std::to_string((int)debugDistance) + " km";
            
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
    
    // POST /api/trips/custom - Plan and return custom tour with user parameters
    CROW_ROUTE(app, "/api/trips/custom").methods("POST"_method)([&tripService, &cityService, &tripCityService](const crow::request& req) {
        try {
            // Debug: Log the incoming request
            std::cout << "🔍 Custom Trip API Request:" << std::endl;
            std::cout << "   Method: " << static_cast<int>(req.method) << std::endl;
            std::cout << "   Body: " << req.body << std::endl;
            std::cout << "   Content-Type: " << req.get_header_value("Content-Type") << std::endl;
            
            // Parse JSON request body
            crow::json::rvalue json = crow::json::load(req.body);
            if (!json) {
                std::cout << "❌ Failed to parse JSON" << std::endl;
                crow::json::wvalue error;
                error["error"] = "Invalid JSON in request body";
                error["expected"] = "{ \"start_city_id\": 1, \"city_ids\": [2, 3, 4, 5] }";
                error["received_body"] = req.body;
                return crow::response(400, error);
            }

            // Extract start city ID
            if (!json.has("start_city_id")) {
                std::cout << "❌ Missing start_city_id field" << std::endl;
                crow::json::wvalue error;
                error["error"] = "Missing required field: start_city_id";
                error["example"] = "{ \"start_city_id\": 1, \"city_ids\": [2, 3, 4] }";
                return crow::response(400, error);
            }
            int startCityId = json["start_city_id"].i();

            // Extract cities to visit
            if (!json.has("city_ids") || json["city_ids"].t() != crow::json::type::List) {
                std::cout << "❌ Missing or invalid field: city_ids (must be array)" << std::endl;
                crow::json::wvalue error;
                error["error"] = "Missing or invalid field: city_ids (must be array)";
                error["example"] = "{ \"start_city_id\": 1, \"city_ids\": [2, 3, 4] }";
                return crow::response(400, error);
            }

            V<int> citiesToVisit;
            for (const auto& cityJson : json["city_ids"]) {
                citiesToVisit.push_back(cityJson.i());
            }

            if (citiesToVisit.size() == 0) {
                std::cout << "❌ At least one city must be specified in city_ids" << std::endl;
                crow::json::wvalue error;
                error["error"] = "At least one city must be specified in city_ids";
                return crow::response(400, error);
            }

            std::cout << "🔍 API: Custom trip request - Start: " << startCityId 
                      << ", Cities: " << citiesToVisit.size() << std::endl;

            // Plan the custom trip with user parameters
            Trip customTrip = tripService.planCustomTour(startCityId, citiesToVisit);
            
            if (customTrip.getId() == 0) {
                crow::json::wvalue error;
                error["error"] = "Failed to create custom tour";
                return crow::response(400, error);
            }
            
            // Get all cities for name lookup
            V<City> allCities = cityService.getAllCities();
            V<TripCity> tripCities = tripCityService.getCitiesForTrip(customTrip.getId());
            
            // Create JSON response (same structure as other trips)
            crow::json::wvalue result;
            result["trip"]["id"] = customTrip.getId();
            result["trip"]["type"] = customTrip.getTripType();
            result["trip"]["start_city_id"] = customTrip.getStartCityId();
            result["trip"]["total_distance"] = customTrip.getTotalDistance();

            // Add debug and multiple formats
            double debugDistance = customTrip.getTotalDistance();
            std::cout << "🔍 API DEBUG: Custom Trip ID = " << customTrip.getId() << std::endl;
            std::cout << "🔍 API DEBUG: Custom Trip distance = " << debugDistance << std::endl;
            std::cout << "🔍 API DEBUG: Custom Trip type = " << customTrip.getTripType() << std::endl;

            result["trip"]["distance"] = debugDistance;
            result["distance"] = debugDistance;
            result["totalDistance"] = debugDistance;
            result["trip"]["totalDistance"] = debugDistance;
            result["trip"]["distance_string"] = std::to_string((int)debugDistance) + " km";
            result["distance_string"] = std::to_string((int)debugDistance) + " km";
            
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


            // ✅ ADD DEBUG AND MULTIPLE FORMATS:
            double debugDistance = berlinTrip.getTotalDistance();
            std::cout << "🔍 API DEBUG: Berlin Trip ID = " << berlinTrip.getId() << std::endl;
            std::cout << "🔍 API DEBUG: Berlin Trip distance = " << debugDistance << std::endl;
            std::cout << "🔍 API DEBUG: Berlin Trip type = " << berlinTrip.getTripType() << std::endl;

            result["trip"]["distance"] = debugDistance;
            result["distance"] = debugDistance;
            result["totalDistance"] = debugDistance;
            result["trip"]["totalDistance"] = debugDistance;
            result["trip"]["distance_string"] = std::to_string((int)debugDistance) + " km";
            result["distance_string"] = std::to_string((int)debugDistance) + " km";


            
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
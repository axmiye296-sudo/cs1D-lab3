/**
 * @file cityRoutes.hpp
 * @brief API route definitions for City-related endpoints
 */

 #ifndef CITY_ROUTES_HPP
 #define CITY_ROUTES_HPP
 
 #include "crow/crow_all.h"
 #include "../services/CityService.hpp"
 #include "../services/FoodService.hpp"
 #include "../repositories/CityDistanceRepository.hpp"
 
 /**
  * @brief Register all city-related API routes
  * @param app Reference to Crow application instance
  * @param cityService Reference to CityService for business logic
  * @param foodService Reference to FoodService for food-related operations
  * @param cityDistanceRepo Reference to CityDistanceRepository for distance calculations
  * 
  * This function sets up all HTTP endpoints related to cities, including:
  * - GET /cities - Retrieve all cities
  * - POST /cities - Create new city (Admin only)
  * - GET /cities/{id} - Get specific city
  * - PUT /cities/{id} - Update city (Admin only)
  * - DELETE /cities/{id} - Delete city (Admin only)
  * - GET /cities/{id}/foods - Get food recommendations for a city
  * - GET /cities/{id}/distances - Get distances to other cities
  */
 void registerCityRoutes(crow::SimpleApp& app, CityService& cityService, FoodService& foodService, CityDistanceRepository& cityDistanceRepo);
 
 #endif
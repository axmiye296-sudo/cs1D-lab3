/**
 * @file tripRoutes.hpp
 * @brief API route definitions for Trip-related endpoints
 */

 #ifndef TRIP_ROUTES_HPP
 #define TRIP_ROUTES_HPP
 
 #include "crow/crow_all.h"
 #include "../services/TripService.hpp"
 #include "../services/CityService.hpp"
 #include "../services/tripCityService.hpp"
 
 /**
  * @brief Register all trip-related API routes
  * @param app Reference to Crow application instance
  * @param tripService Reference to TripService for trip planning logic
  * @param cityService Reference to CityService for city operations
  * @param tripCityService Reference to TripCityService for trip-city relationships
  * 
  * This function sets up all HTTP endpoints related to trips, including:
  * - GET /trips - Get all trips
  * - POST /trips - Create new trip
  * - GET /trips/{id} - Get specific trip
  * - PUT /trips/{id} - Update trip
  * - DELETE /trips/{id} - Delete trip
  * - POST /trips/plan/paris - Plan Paris tour
  * - POST /trips/plan/london - Plan London tour
  * - POST /trips/plan/berlin - Plan Berlin tour
  * - POST /trips/plan/custom - Plan custom tour
  * - GET /trips/{id}/cities - Get cities in a trip
  * - POST /trips/{id}/cities - Add city to trip
  * - DELETE /trips/{id}/cities/{cityId} - Remove city from trip
  * - PUT /trips/{id}/cities/{cityId}/order - Update city visit order
  */
 void registerTripRoutes(crow::SimpleApp& app, TripService& tripService, CityService& cityService, TripCityService& tripCityService);
 
 #endif
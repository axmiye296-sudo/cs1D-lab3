/**
 * TripCity Service Implementation
 * Business logic and validation for trip-city operations
 * Enforces business rules and provides clean API
 */

#include "../include/tripCityService.hpp"
#include <iostream>

TripCityService::TripCityService(TripCityDataAccess& access) : dataAccess(access) {}

bool TripCityService::addCityToTrip(int tripId, int cityId, int visitOrder) {
    // Auto-assign visit order if not provided
    if (visitOrder == -1) {
        visitOrder = dataAccess.getNextVisitOrder(tripId);
    }
    
    // Validate parameters
    if (!validateTripCity(tripId, cityId, visitOrder)) {
        return false;
    }
    
    // Add city to trip
    return dataAccess.addCityToTrip(tripId, cityId, visitOrder);
}

V<TripCity> TripCityService::getCitiesForTrip(int tripId) {
    return dataAccess.getCitiesForTrip(tripId);
}

bool TripCityService::removeCityFromTrip(int tripId, int cityId) {
    return dataAccess.removeCityFromTrip(tripId, cityId);
}

bool TripCityService::reorderCities(int tripId, const V<TripCity>& newOrder) {
    // Remove all existing cities for this trip
    V<TripCity> existingCities = dataAccess.getCitiesForTrip(tripId);
    for (const auto& city : existingCities) {
        dataAccess.removeCityFromTrip(tripId, city.getCityId());
    }
    
    // Add cities in new order
    for (size_t i = 0; i < newOrder.size(); i++) {
        if (!dataAccess.addCityToTrip(tripId, newOrder[i].getCityId(), i + 1)) {
            return false;
        }
    }
    
    return true;
}

void TripCityService::printTripCities(int tripId) {
    V<TripCity> cities = getCitiesForTrip(tripId);
    std::cout << "\n=== Cities in Trip " << tripId << " ===" << std::endl;
    for (const auto& city : cities) {
        std::cout << "City ID: " << city.getCityId() 
                  << ", Visit Order: " << city.getVisitOrder() << std::endl;
    }
    std::cout << "Total cities: " << cities.size() << std::endl;
}

bool TripCityService::validateTripCity(int tripId, int cityId, int visitOrder) {
    if (tripId <= 0 || cityId <= 0 || visitOrder <= 0) {
        std::cerr << "Error: Invalid parameters (tripId: " << tripId 
                  << ", cityId: " << cityId << ", visitOrder: " << visitOrder << ")" << std::endl;
        return false;
    }
    
    return true;
}




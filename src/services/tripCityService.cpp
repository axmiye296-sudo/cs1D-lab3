/**
 * TripCity Service Implementation - SQLite Only
 * Business logic and validation for trip-city operations
 */

#include "../include/services/tripCityService.hpp"
#include <iostream>
#include <iomanip> // Required for std::setw

TripCityService::TripCityService(TripCityRepository& repository) : repo(repository) {}

bool TripCityService::addCityToTrip(int tripId, int cityId, int visitOrder) {
    if (visitOrder == -1) {
        visitOrder = getNextVisitOrder(tripId);
    }
    
    if (!validateTripCity(tripId, cityId, visitOrder)) {
        return false;
    }
    
    if (cityExistsInTrip(tripId, cityId)) {
        std::cout << "City " << cityId << " already exists in trip " << tripId << std::endl;
        return false;
    }
    
    TripCity tripCity(0, tripId, cityId, visitOrder);
    return repo.save(tripCity);
}

V<TripCity> TripCityService::getCitiesForTrip(int tripId) {
    return repo.findByTrip(tripId);
}

bool TripCityService::removeCityFromTrip(int tripId, int cityId) {
    // Get all cities for this trip
    V<TripCity> cities = repo.findByTrip(tripId);
    
    // Find the city to remove
    for (const auto& city : cities) {
        if (city.getCityId() == cityId) {
            return repo.remove(city.getId());
        }
    }
    
    return false; // City not found in trip
}

bool TripCityService::updateVisitOrder(int tripId, int cityId, int newOrder) {
    // Get all cities for this trip
    V<TripCity> cities = repo.findByTrip(tripId);
    
    // Find the city to update
    for (const auto& city : cities) {
        if (city.getCityId() == cityId) {
            TripCity updatedCity = city;
            updatedCity.setVisitOrder(newOrder);
            return repo.save(updatedCity);
        }
    }
    
    return false; // City not found in trip
}

bool TripCityService::cityExistsInTrip(int tripId, int cityId) {
    V<TripCity> cities = repo.findByTrip(tripId);
    
    for (const auto& city : cities) {
        if (city.getCityId() == cityId) {
            return true;
        }
    }
    
    return false;
}

int TripCityService::getNextVisitOrder(int tripId) {
    V<TripCity> cities = repo.findByTrip(tripId);
    
    int maxOrder = 0;
    for (const auto& city : cities) {
        maxOrder = std::max(maxOrder, city.getVisitOrder());
    }
    
    return maxOrder + 1;
}

void TripCityService::printTripCities(int tripId) {
    V<TripCity> cities = getCitiesForTrip(tripId);
    
    std::cout << "\n=== Cities in Trip " << tripId << " ===" << std::endl;
    
    if (cities.empty()) {
        std::cout << "No cities found in this trip." << std::endl;
        return;
    }
    
    std::cout << std::setw(5) << "ID" << " | " << std::setw(8) << "City ID" << " | " 
              << std::setw(12) << "Visit Order" << std::endl;
    std::cout << std::string(30, '-') << std::endl;
    
    for (const auto& city : cities) {
        std::cout << std::setw(5) << city.getId() << " | " 
                  << std::setw(8) << city.getCityId() << " | " 
                  << std::setw(12) << city.getVisitOrder() << std::endl;
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




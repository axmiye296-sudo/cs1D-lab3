#include "../../include/services/TripCityService.hpp"

TripCityService::TripCityService(std::unique_ptr<TripCityRepository> repo) 
    : repository(std::move(repo)) {}

bool TripCityService::addCityToTrip(int tripId, int cityId, int visitOrder) {
    // Business validation
    if (!validateTripCity(tripId, cityId, visitOrder)) {
        return false;
    }
    
    // Create and save TripCity
    TripCity tripCity(tripId, cityId, visitOrder);
    return repository->save(tripCity);
}

bool TripCityService::removeCityFromTrip(int tripId, int cityId) {
    V<TripCity> cities = repository->findByTrip(tripId);
    
    for (size_t i = 0; i < cities.size(); i++) {
        if (cities[i].getCityId() == cityId) {
            return repository->remove(cities[i].getId());
        }
    }
    return false;
}

V<TripCity> TripCityService::getCitiesForTrip(int tripId) {
    return repository->findByTrip(tripId);
}

bool TripCityService::reorderCities(int tripId, const V<TripCity>& newOrder) {
    return repository->reorderTripCities(tripId, newOrder);
}

bool TripCityService::validateTripCity(int tripId, int cityId, int visitOrder) {
    // Simple business rules
    if (tripId <= 0 || cityId <= 0 || visitOrder <= 0) {
        std::cerr << "Error: Invalid parameters" << std::endl;
        return false;
    }
    
    // Check if city already in trip
    V<TripCity> existingCities = repository->findByTrip(tripId);
    for (size_t i = 0; i < existingCities.size(); i++) {
        if (existingCities[i].getCityId() == cityId) {
            std::cerr << "Error: City already in trip" << std::endl;
            return false;
        }
    }
    
    return true;
}
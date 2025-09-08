#ifndef TRIP_CITY_SERVICE_HPP
#define TRIP_CITY_SERVICE_HPP

#include "../V.hpp"
#include "../entities/tripCities.hpp"
#include "../repositories/TripCityRepository.hpp"

class TripCityService {
private:
    std::unique_ptr<TripCityRepository> repository;
    
public:
    TripCityService(std::unique_ptr<TripCityRepository> repo);
    
    // Simple business operations
    bool addCityToTrip(int tripId, int cityId, int visitOrder);
    bool removeCityFromTrip(int tripId, int cityId);
    V<TripCity> getCitiesForTrip(int tripId);
    bool reorderCities(int tripId, const V<TripCity>& newOrder);
    
private:
    bool validateTripCity(int tripId, int cityId, int visitOrder);
};

#endif
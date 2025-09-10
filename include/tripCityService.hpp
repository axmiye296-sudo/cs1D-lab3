/**
 * TripCity Service Layer
 * Business logic for trip-city operations
 * Validates data and enforces business rules
 */

#ifndef TRIP_CITY_SERVICE_HPP
#define TRIP_CITY_SERVICE_HPP

#include "header.hpp"
#include "entities/tripCities.hpp"
#include "tripCityDataAccess.hpp"

class TripCityService {
private:
    TripCityDataAccess& dataAccess;

public:
    TripCityService(TripCityDataAccess& access);
    
    // Business operations
    bool addCityToTrip(int tripId, int cityId, int visitOrder = -1);
    V<TripCity> getCitiesForTrip(int tripId);
    bool removeCityFromTrip(int tripId, int cityId);
    bool reorderCities(int tripId, const V<TripCity>& newOrder);
    
    // Utility
    void printTripCities(int tripId);
    
private:
    bool validateTripCity(int tripId, int cityId, int visitOrder);
};

#endif


/**
 * TripCity Data Access Layer
 * Handles database operations for trip-city relationships
 * Converts between JSON data and TripCity objects
 */

#ifndef TRIP_CITY_DATA_ACCESS_HPP
#define TRIP_CITY_DATA_ACCESS_HPP

#include "header.hpp"
#include "entities/tripCities.hpp"
#include "jsonDatabase.hpp"

class TripCityDataAccess {
private:
    JsonDatabase& db;

public:
    TripCityDataAccess(JsonDatabase& database);
    
    // Raw CRUD operations (no SQL)
    bool addCityToTrip(int tripId, int cityId, int visitOrder);
    V<TripCity> getCitiesForTrip(int tripId);
    bool removeCityFromTrip(int tripId, int cityId);
    bool updateVisitOrder(int tripId, int cityId, int newOrder);
    bool cityExistsInTrip(int tripId, int cityId);
    int getNextVisitOrder(int tripId);
    
    // Utility
    void printAllTripCities();
};

#endif

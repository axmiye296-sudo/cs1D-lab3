#ifndef TRIP_CITY_SERVICE_HPP
#define TRIP_CITY_SERVICE_HPP

#include "../header.hpp"
#include "../repositories/TripCityRepository.hpp"
#include "../entities/tripCities.hpp"
#include <iomanip>

class TripCityService {
private:
    TripCityRepository& repo;  // Changed from DatabaseManager& db
    
public:
    TripCityService(TripCityRepository& repository);  // Changed parameter type
    
    // Core operations
    bool addCityToTrip(int tripId, int cityId, int visitOrder = -1);
    V<TripCity> getCitiesForTrip(int tripId);
    bool removeCityFromTrip(int tripId, int cityId);
    bool updateVisitOrder(int tripId, int cityId, int newOrder);
    
    // Utility operations
    bool cityExistsInTrip(int tripId, int cityId);
    int getNextVisitOrder(int tripId);
    void printTripCities(int tripId);
    
    // Validation
    bool validateTripCity(int tripId, int cityId, int visitOrder);
};

#endif

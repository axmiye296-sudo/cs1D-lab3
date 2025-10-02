#ifndef TRIP_SERVICE_HPP
#define TRIP_SERVICE_HPP

#include "../header.hpp"
#include "../entities/Trip.hpp"
#include "../entities/TripCity.hpp"
#include "../repositories/TripRepository.hpp"
#include "../repositories/CityDistanceRepository.hpp"
#include "../services/tripCityService.hpp"

class TripService {
private:
    TripRepository& tripRepo;
    CityDistanceRepository& cityDistanceRepo;
    TripCityService& tripCityService;

    // Helper methods moved from Trip entity
    bool hasCity(const Trip& trip, int cityId);
    int getTripSize(const Trip& trip);
    void addCityToTrip(Trip& trip, int cityId);

    // Recursive trip planning methods
    int findNearestUnvisitedCity(Trip& trip, int fromCityId);
    void CreateShortestTrip(Trip& trip, int startCityId);
    void CreateShortestTrip(Trip& trip, int startCityId, const V<int>& allowedCities);
    int findNearestUnvisitedCityFromList(Trip& trip, int fromCityId, const V<int>& allowedCities);

public:
    TripService(TripRepository& tripRepository, CityDistanceRepository& cityDistanceRepo, TripCityService& tripCityService);
    
    // Main trip planning methods
    Trip planParisTour();
    Trip planLondonTour(int numCities = 13);
    Trip planCustomTour(int startCityId, const V<int>& citiesToVisit);
    Trip planBerlinTour();
};

#endif
#ifndef TRIP_SERVICE_HPP
#define TRIP_SERVICE_HPP

#include "../header.hpp"
#include "../entities/Trip.hpp"
#include "../entities/City.hpp"
#include "../entities/Food.hpp"
#include "../repositories/CityRepository.hpp"
#include "../repositories/TripRepository.hpp"
#include "../services/FoodService.hpp"
#include "../services/tripCityService.hpp"

class TripService {
private:
    TripRepository& tripRepo;
    CityRepository& cityRepo;
    TripCityService& tripCityService;
    FoodService& foodService;

    // Private helper methods
    V<int> calculateOptimalRoute(int startCityId, const V<int>& citiesToVisit);
    int findClosestCity(int currentCityId, const V<int>& remainingCities);
    double calculateTotalDistance(const V<int>& cityRoute);
    Trip createAndSaveTrip(int startCityId, const std::string& tripType, const V<int>& cityRoute);
    int findCityIdByName(const std::string& cityName);
    void displayAvailableCities();
    void displayTripCities(int tripId);

public:
    TripService(TripRepository& tripRepo, CityRepository& cityRepo,
        TripCityService& tripCityService, FoodService& foodService);

    // Main trip planning methods
    Trip planParisTour();
    Trip planLondonTour();
    Trip planCustomTour();
    Trip planBerlinTour();

    // Simple trip display (no purchases needed)
    void displayTrip(const Trip& trip);
};

#endif
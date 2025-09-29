#ifndef TRIP_SERVICE_HPP
#define TRIP_SERVICE_HPP

#include "../header.hpp"
#include "../repositories/TripRepository.hpp"
#include "../repositories/CityDistanceRepository.hpp"
#include "../entities/Trip.hpp"

class TripService
{
    private:
        TripRepository& tripRepo;
        CityDistanceRepository& cityDistanceRepo;

    public:
          TripService(TripRepository& tripRepository,
                CityDistanceRepository& cityRepo);
 
        //Creating the overall trip
        void CreateShortestTrip (Trip& trip, int startCityId); //Story 2
        void CreateCustomTrip (Trip& trip, int startCityId);
           
        int findNearestUnvisitedCity(Trip& trip, int fromCityId);


};


#endif
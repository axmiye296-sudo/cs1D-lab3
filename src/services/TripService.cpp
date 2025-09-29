#include "../include/services/TripService.hpp" 
#include "../include/entities/CityDistance.hpp" 
#include <iostream>
#include <iomanip>
#include <limits>

TripService::TripService(TripRepository& tripRepository,
                         CityDistanceRepository& cityRepo)
    : tripRepo(tripRepository), cityDistanceRepo(cityRepo) {}

int TripService::findNearestUnvisitedCity(Trip& trip, int fromCityId) {
    auto distances   = cityDistanceRepo.findByFromCity(fromCityId);   //2
    int nearestCityId = -1;                                           //3
    int minDistance   = std::numeric_limits<int>::max();              //3

    for (const auto& row : distances) {                               //4
        int candidate = row.getToCityId();                            //5
        int distance  = row.getDistance();                            //5

        // ⬇️ Skip the start city so we never return to Paris
        if (candidate == trip.getStartCityId()) continue;

        if (!trip.hasCity(candidate) && distance < minDistance) {     //6
            minDistance   = distance;
            nearestCityId = candidate;
        }
    }
    return nearestCityId; // -1 if none found
}

void TripService::CreateShortestTrip(Trip &trip, int startCityId)
{
	if (trip.getTripType() != "custom") { return; }                 //1
	if (trip.getTripSize() == 11) { return; }                  //2 - 11 forn ow, should be replaced by some getMaxTripSize() function later
	else
	{
		int nextCityId = findNearestUnvisitedCity(trip, startCityId);      //3
        if (nextCityId == -1) return;
        int legDistance = cityDistanceRepo.getDistance(startCityId, nextCityId);
        trip.setTotalDistance(trip.getTotalDistance() + legDistance);
		trip.addTC(trip, nextCityId);                     //4
		return CreateShortestTrip(trip, nextCityId);                //5
	}
}


#ifndef TRIP_REPOSITORY_HPP
#define TRIP_REPOSITORY_HPP

#include "../header.hpp"
#include "../databaseManager.hpp"
#include "../entities/Trip.hpp"
#include "../entities/TripCity.hpp"

class TripRepository
{
    private:
        DatabaseManager& db;

    public:
        TripRepository(DatabaseManager& database);

        //CRUD
		bool save(Trip& trip);
		bool load(int id, Trip& trip);
		bool remove(int id);
		
		//Trip Queries
		// Trip CreateShortestTrip(int count, int startCityId); //shortest, fixed trip
		// Trip CreateCustomShortestTrip(int startCityId); //shortest, custom trip
        //

    private:
        //Helper methods
        
        
};

#endif
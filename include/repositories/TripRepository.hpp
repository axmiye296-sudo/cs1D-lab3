#ifndef TRIP_REPOSITORY_HPP
#define TRIP_REPOSITORY_HPP

#include "../header.hpp"
#include "../entities/Trip.hpp"

class DatabaseManager;

class TripRepository {
private:
    DatabaseManager& database;

public:
    TripRepository(DatabaseManager& database);

    // This function will return a vector of trip objects
    // that match the trip type (starting city)
    V<Trip> findByType(const std::string& tripType);

    // This function is for custom start city
    V<Trip> findByStartCity(int startCityId);

    // This will convert a row from the trip table into a
    // Trip object
    Trip mapRowToEntity(const std::vector<std::string>& row);

    // This function will create a new trip record in the
    // trip table
    std::string buildInsertQuery(const Trip& trip);

    // This function will create an SQL update statement to
    // update an existing trip record in the database
    std::string buildUpdateQuery(const Trip& trip);


    bool save(Trip& trip);                    // Save/update trip
    bool load(int id, Trip& trip);           // Load trip by ID

};

#endif
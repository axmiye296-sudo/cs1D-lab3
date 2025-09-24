#ifndef TRIP_REPOSITORY_HPP
#define TRIP_REPOSITORY_HPP

#include "../DatabaseManager.hpp"
#include "../models/Trip.hpp"

class TripRepository {
private:
    DatabaseManager& db;

public:
    TripRepository(DatabaseManager& database);
    ~TripRepository();

    bool save(Trip& trip);           // insert or update
    bool remove(int id);             // delete by id
    Trip findById(int id);           // get trip by id
    V<Trip> findAll();               // get all trips
};

#endif // TRIP_REPOSITORY_HPP


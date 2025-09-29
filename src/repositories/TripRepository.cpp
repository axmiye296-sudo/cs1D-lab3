#ifndef TRIP_CITY_REPOSITORY_HPP
#define TRIP_CITY_REPOSITORY_HPP

#include "../../include/repositories/TripRepository.hpp"
TripRepository::TripRepository(DatabaseManager& database)
    : db(database) {}
// CREATE or UPDATE
bool TripRepository::save(Trip& trip) {
    if (!db.isConnected()) {
        std::cerr << "[TripRepository::save] DB not connected\n";
        return false;
    }

    // INSERT
    if (trip.getId() == 0) {
        std::string q =
            "INSERT INTO trips (start_city_id, trip_type, total_distance) VALUES (" +
            std::to_string(trip.getStartCityId()) + ", '" +
            trip.getTripType() + "', " +
            std::to_string(trip.getTotalDistance()) + ");";

        int newId = db.executeInsert(q);
        if (newId <= 0) return false;
        trip.setId(newId);
        return true;
    } 
    // UPDATE
    else {
        std::string q =
            "UPDATE trips SET "
            "start_city_id = " + std::to_string(trip.getStartCityId()) + ", " +
            "trip_type = '" + trip.getTripType() + "', " +
            "total_distance = " + std::to_string(trip.getTotalDistance()) +
            " WHERE id = " + std::to_string(trip.getId()) + ";";

        return db.executeUpdate(q);
    }
}

// READ
bool TripRepository::load(int id, Trip& trip) {
    if (!db.isConnected()) {
        std::cerr << "[TripRepository::load] DB not connected\n";
        return false;
    }

    std::string q =
        "SELECT id, start_city_id, trip_type, total_distance "
        "FROM trips WHERE id = " + std::to_string(id) + ";";

    auto rows = db.executeSelect(q);
    if (rows.empty() || rows[0].size() < 4) return false;

    const auto& r = rows[0];
    trip.setId(std::stoi(r[0]));
    trip.setStartCityId(std::stoi(r[1]));
    trip.setTripType(r[2]);
    trip.setTotalDistance(std::stoi(r[3]));
    return true;
}

// DELETE
bool TripRepository::remove(int id) {
    if (!db.isConnected()) {
        std::cerr << "[TripRepository::remove] DB not connected\n";
        return false;
    }

    std::string q = "DELETE FROM trips WHERE id = " + std::to_string(id) + ";";
    return db.executeDelete(q);
}

#endif
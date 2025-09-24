#include "../include/repositories/TripRepository.hpp"
#include <sqlite3.h>
#include <iostream>

TripRepository::TripRepository(DatabaseManager& database) : db(database) {}
TripRepository::~TripRepository() {}

bool TripRepository::save(Trip& trip) {
    sqlite3* conn = db.getConnection();
    sqlite3_stmt* stmt;

    if (trip.getId() == 0) {
        const char* sql = "INSERT INTO trips (start_city_id, trip_type, total_distance) VALUES (?, ?, ?);";
        if (sqlite3_prepare_v2(conn, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;

        sqlite3_bind_int(stmt, 1, trip.getStartCityId());
        sqlite3_bind_text(stmt, 2, trip.getTripType().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 3, trip.getTotalDistance());

        bool success = sqlite3_step(stmt) == SQLITE_DONE;
        if (success) trip.setId((int)sqlite3_last_insert_rowid(conn));

        sqlite3_finalize(stmt);
        return success;
    } else {
        const char* sql = "UPDATE trips SET start_city_id=?, trip_type=?, total_distance=? WHERE id=?;";
        if (sqlite3_prepare_v2(conn, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;

        sqlite3_bind_int(stmt, 1, trip.getStartCityId());
        sqlite3_bind_text(stmt, 2, trip.getTripType().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 3, trip.getTotalDistance());
        sqlite3_bind_int(stmt, 4, trip.getId());

        bool success = sqlite3_step(stmt) == SQLITE_DONE;
        sqlite3_finalize(stmt);
        return success;
    }
}

bool TripRepository::remove(int id) {
    sqlite3* conn = db.getConnection();
    sqlite3_stmt* stmt;

    const char* sql = "DELETE FROM trips WHERE id=?;";
    if (sqlite3_prepare_v2(conn, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;

    sqlite3_bind_int(stmt, 1, id);
    bool success = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return success;
}

Trip TripRepository::findById(int id) {
    sqlite3* conn = db.getConnection();
    sqlite3_stmt* stmt;
    Trip trip;

    const char* sql = "SELECT id, start_city_id, trip_type, total_distance FROM trips WHERE id=?;";
    if (sqlite3_prepare_v2(conn, sql, -1, &stmt, nullptr) != SQLITE_OK) return trip;

    sqlite3_bind_int(stmt, 1, id);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        trip.setId(sqlite3_column_int(stmt, 0));
        trip.setStartCityId(sqlite3_column_int(stmt, 1));
        trip.setTripType((const char*)sqlite3_column_text(stmt, 2));
        trip.setTotalDistance(sqlite3_column_int(stmt, 3));
    }
    sqlite3_finalize(stmt);
    return trip;
}

 V<Trip> TripRepository::findAll() {
    sqlite3* conn = db.getConnection();
    sqlite3_stmt* stmt;
    V<Trip> trips;

    const char* sql = "SELECT id, start_city_id, trip_type, total_distance FROM trips;";
    if (sqlite3_prepare_v2(conn, sql, -1, &stmt, nullptr) != SQLITE_OK) return trips;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Trip trip;
        trip.setId(sqlite3_column_int(stmt, 0));
        trip.setStartCityId(sqlite3_column_int(stmt, 1));
        trip.setTripType((const char*)sqlite3_column_text(stmt, 2));
        trip.setTotalDistance(sqlite3_column_int(stmt, 3));
        trips.push_back(trip);
    }
    sqlite3_finalize(stmt);
    return trips;
}

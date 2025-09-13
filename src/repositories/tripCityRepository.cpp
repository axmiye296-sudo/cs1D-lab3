#include "../include/repositories/TripCityRepository.hpp"
#include <iostream>

TripCityRepository::TripCityRepository(DatabaseManager& database) : db(database) {}

bool TripCityRepository::save(TripCity& tripCity) {
    std::string query;
    if (tripCity.getId() == 0) {
        // Insert new
        query = buildInsertQuery(tripCity);
    } else {
        // Update existing
        query = buildUpdateQuery(tripCity);
    }
    
    return db.executeQuery(query);
}

V<TripCity> TripCityRepository::findByTrip(int tripId) {
    V<TripCity> result;
    std::string query = buildSelectByTripQuery(tripId);
    auto dbResult = db.executeSelect(query);
    
    if (!dbResult.empty()) {
        for (const auto& row : dbResult) {
            if (row.size() >= 4) {
                TripCity tripCity = mapRowToEntity(row);
                result.push_back(tripCity);
            }
        }
    }
    
    return result;
}

bool TripCityRepository::remove(int id) {
    std::string query = buildDeleteQuery(id);
    return db.executeQuery(query);
}

// Add missing methods
V<TripCity> TripCityRepository::findAll() {
    V<TripCity> result;
    std::string query = buildSelectAllQuery();
    auto dbResult = db.executeSelect(query);
    
    if (!dbResult.empty()) {
        for (const auto& row : dbResult) {
            if (row.size() >= 4) {
                TripCity tripCity = mapRowToEntity(row);
                result.push_back(tripCity);
            }
        }
    }
    
    return result;
}

bool TripCityRepository::load(int id, TripCity& tripCity) {
    std::string query = buildSelectQuery(id);
    auto dbResult = db.executeSelect(query);
    
    if (!dbResult.empty() && dbResult[0].size() >= 4) {
        tripCity = mapRowToEntity(dbResult[0]);
        return true;
    }
    
    return false;
}

V<TripCity> TripCityRepository::findByCity(int cityId) {
    V<TripCity> result;
    std::string query = "SELECT id, trip_id, city_id, visit_order FROM trip_cities WHERE city_id = " + 
                       std::to_string(cityId) + " ORDER BY visit_order;";
    auto dbResult = db.executeSelect(query);
    
    if (!dbResult.empty()) {
        for (const auto& row : dbResult) {
            if (row.size() >= 4) {
                TripCity tripCity = mapRowToEntity(row);
                result.push_back(tripCity);
            }
        }
    }
    
    return result;
}

bool TripCityRepository::existsByTripAndOrder(int tripId, int visitOrder) {
    std::string query = "SELECT COUNT(*) FROM trip_cities WHERE trip_id = " + std::to_string(tripId) + 
                       " AND visit_order = " + std::to_string(visitOrder) + ";";
    auto dbResult = db.executeSelect(query);
    
    if (!dbResult.empty() && !dbResult[0].empty()) {
        int count = std::stoi(dbResult[0][0]);
        return count > 0;
    }
    
    return false;
}

bool TripCityRepository::saveAll(const V<TripCity>& tripCities) {
    for (const auto& tripCity : tripCities) {
        TripCity temp = tripCity; // Create non-const copy
        if (!save(temp)) {
            return false;
        }
    }
    return true;
}

bool TripCityRepository::removeByTrip(int tripId) {
    std::string query = "DELETE FROM trip_cities WHERE trip_id = " + std::to_string(tripId) + ";";
    return db.executeQuery(query);
}

// Helper methods
TripCity TripCityRepository::mapRowToEntity(const std::vector<std::string>& row) {
    int id = std::stoi(row[0]);
    int tripId = std::stoi(row[1]);
    int cityId = std::stoi(row[2]);
    int visitOrder = std::stoi(row[3]);
    
    return TripCity(id, tripId, cityId, visitOrder);
}

std::string TripCityRepository::buildInsertQuery(const TripCity& tripCity) {
    return "INSERT INTO trip_cities (trip_id, city_id, visit_order) VALUES (" +
           std::to_string(tripCity.getTripId()) + ", " +
           std::to_string(tripCity.getCityId()) + ", " +
           std::to_string(tripCity.getVisitOrder()) + ");";
}

std::string TripCityRepository::buildUpdateQuery(const TripCity& tripCity) {
    return "UPDATE trip_cities SET trip_id = " + std::to_string(tripCity.getTripId()) +
           ", city_id = " + std::to_string(tripCity.getCityId()) +
           ", visit_order = " + std::to_string(tripCity.getVisitOrder()) +
           " WHERE id = " + std::to_string(tripCity.getId()) + ";";
}

std::string TripCityRepository::buildDeleteQuery(int id) {
    return "DELETE FROM trip_cities WHERE id = " + std::to_string(id) + ";";
}

std::string TripCityRepository::buildSelectQuery(int id) {
    return "SELECT id, trip_id, city_id, visit_order FROM trip_cities WHERE id = " + std::to_string(id) + ";";
}

std::string TripCityRepository::buildSelectAllQuery() {
    return "SELECT id, trip_id, city_id, visit_order FROM trip_cities ORDER BY trip_id, visit_order;";
}

std::string TripCityRepository::buildSelectByTripQuery(int tripId) {
    return "SELECT id, trip_id, city_id, visit_order FROM trip_cities WHERE trip_id = " + 
           std::to_string(tripId) + " ORDER BY visit_order;";
}





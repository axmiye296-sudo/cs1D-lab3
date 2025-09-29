
#include "../../include/repositories/CityDistanceRepository.hpp"
#include <iostream>
CityDistanceRepository::CityDistanceRepository(DatabaseManager& database)
: db(database) {}

// Return all rows where from_city_id = given id
V<CityDistance> CityDistanceRepository::findByFromCity(int fromCityId) {
    V<CityDistance> result;

    std::string query = buildSelectByFromCityQuery(fromCityId);
    auto dbResult = db.executeSelect(query);

    if (!dbResult.empty()) {
        for (const auto& row : dbResult) {
            if (row.size() >= 3) { // [from_city_id, to_city_id, distance]
                result.push_back(mapRowToEntity(row));
            }
        }
    }
    return result;
}

int CityDistanceRepository::getDistance(int fromCityId, int toCityId) {
    std::string query = buildSelectDistanceQuery(fromCityId, toCityId);
    auto result = db.executeSelect(query);

    if (!result.empty() && !result[0].empty()) {
        return std::stoi(result[0][0]);
    }
    return 0; // or -1 if you want to signal "not found"
}


// ===================== Helpers =====================

CityDistance CityDistanceRepository::mapRowToEntity(const std::vector<std::string>& row) {
    // row format: [from_city_id, to_city_id, distance]
    int fromId    = std::stoi(row[0]);
    int toId      = std::stoi(row[1]);
    double dist   = std::stod(row[2]);
    return CityDistance(fromId, toId, dist);
}

std::string CityDistanceRepository::buildSelectByFromCityQuery(int fromCityId) {
    return "SELECT from_city_id, to_city_id, distance "
           "FROM city_distances "
           "WHERE from_city_id = " + std::to_string(fromCityId) + ";";
}

std::string CityDistanceRepository::buildSelectNearestQuery(int fromCityId) {
    return "SELECT to_city_id, distance "
           "FROM city_distances "
           "WHERE from_city_id = " + std::to_string(fromCityId) + " "
           "ORDER BY distance ASC "
           "LIMIT 1;";
}

std::string CityDistanceRepository::buildSelectDistanceQuery(int fromCityId, int toCityId) {
    return "SELECT distance "
           "FROM city_distances "
           "WHERE from_city_id = " + std::to_string(fromCityId) + " "
           "AND to_city_id = " + std::to_string(toCityId) + ";";
}
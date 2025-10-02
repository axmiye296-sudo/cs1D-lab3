#ifndef CITY_DISTANCE_REPOSITORY_HPP
#define CITY_DISTANCE_REPOSITORY_HPP

#include "../header.hpp"
#include "../entities/CityDistance.hpp"
#include "../databaseManager.hpp"

class CityDistanceRepository {
private:
    DatabaseManager& database;

public:
    CityDistanceRepository(DatabaseManager& db);
    
    V<CityDistance> findByFromCity(int fromCityId);
    int getDistance(int fromCityId, int toCityId);
    V<CityDistance> findAll();

private:
    CityDistance mapRowToEntity(const std::vector<std::string>& row);
};

#endif

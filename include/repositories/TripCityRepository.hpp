#ifndef TRIP_CITY_REPOSITORY_HPP
#define TRIP_CITY_REPOSITORY_HPP

#include "../header.hpp"
#include "../databaseManager.hpp"
#include "../entities/tripCities.hpp"

class TripCityRepository {
private:
    DatabaseManager& db;
    
public:
    TripCityRepository(DatabaseManager& database);
    
    // CRUD operations
    bool save(TripCity& tripCity);
    bool load(int id, TripCity& tripCity);
    bool remove(int id);
    V<TripCity> findAll();
    
    // TripCity-specific queries
    V<TripCity> findByTrip(int tripId);
    V<TripCity> findByCity(int cityId);
    bool existsByTripAndOrder(int tripId, int visitOrder);
    
    // Batch operations
    bool saveAll(const V<TripCity>& tripCities);
    bool removeByTrip(int tripId);
    
private:
    // Helper methods
    TripCity mapRowToEntity(const std::vector<std::string>& row);
    std::string buildInsertQuery(const TripCity& tripCity);
    std::string buildUpdateQuery(const TripCity& tripCity);
    std::string buildDeleteQuery(int id);
    std::string buildSelectQuery(int id);
    std::string buildSelectAllQuery();
    std::string buildSelectByTripQuery(int tripId);
};

#endif

#ifndef TRIP_CITY_REPOSITORY_HPP
#define TRIP_CITY_REPOSITORY_HPP

#include "IRepository.hpp"
#include "../databaseManager.hpp"
#include "../entities/tripCities.hpp"

class TripCityRepository : public IRepository<TripCity> {
private:
    DatabaseManager& db;
    
public:
    TripCityRepository(DatabaseManager& database);
    
    // CRUD operations
    bool save(TripCity& tripCity) override;
    bool load(int id, TripCity& tripCity) override;
    bool remove(int id) override;
    V<TripCity> findAll() override;
    
    // TripCity-specific queries
    V<TripCity> findByTrip(int tripId);
    V<TripCity> findByCity(int cityId);
    V<TripCity> findByTripAndCity(int tripId, int cityId);
    bool existsByTripAndOrder(int tripId, int visitOrder);
    
    // Batch operations
    bool saveAll(const V<TripCity>& tripCities);
    bool removeByTrip(int tripId);
    bool reorderTripCities(int tripId, const V<TripCity>& newOrder);
    
    // Transaction support
    bool beginTransaction() override;
    bool commitTransaction() override;
    bool rollbackTransaction() override;
    
private:
    // Helper methods
    TripCity mapRowToEntity(const std::vector<std::string>& row);
    std::string buildInsertQuery(const TripCity& tripCity);
    std::string buildUpdateQuery(const TripCity& tripCity);
    std::string buildDeleteQuery(int id);
    std::string buildSelectQuery(int id);
    std::string buildSelectAllQuery();
    std::string buildSelectByTripQuery(int tripId);
    std::string buildSelectByCityQuery(int cityId);
};

#endif
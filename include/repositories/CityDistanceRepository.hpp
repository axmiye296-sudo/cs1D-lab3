#ifndef CITY_DISTANCE_REPOSITORY_HPP
#define CITY_DISTANCE_REPOSITORY_HPP


#include "../header.hpp"
#include "../databaseManager.hpp"
#include "../entities/CityDistance.hpp"

class CityDistanceRepository{
    private:
        DatabaseManager& db;
    public:
        CityDistanceRepository(DatabaseManager & database);
        
        //CRUD
        bool save(CityDistance& cityDistance);          //Create & Update
        bool load(int id, CityDistance& cityDistance);  //Read
        bool remove(int id);                            //Delete

        V<CityDistance> findByFromCity(int fromCityId);
        int getDistance(int fromCityId, int toCityId);

        
        //helper functions
        CityDistance mapRowToEntity(const std::vector<std::string>& row);
        std::string buildSelectByFromCityQuery(int fromCityId);
        std::string buildSelectNearestQuery(int fromCityId);
        std::string buildSelectDistanceQuery(int fromCityId, int toCityId);


};

#endif
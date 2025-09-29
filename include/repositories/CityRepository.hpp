#ifndef CITY_REPOSITORY_HPP
#define CITY_REPOSITORY_HPP

#include "../header.hpp"
#include "../databaseManager.hpp"

class CityRepository
{
    private:
        DatabaseManager& db;

    public:
        CityRepository(DatabaseManager &db);
        std::string getCityNameById(int cityId);

};


#endif
#ifndef CITY_REPOSITORY_HPP
#define CITY_REPOSITORY_HPP

#include "../header.hpp"
#include "../entities/City.hpp"

class CityRepository {
  private:
  DatabaseManager& database;  // Reference to our database connection - we need this to run SQL querie;

  public:
    CityRepository(DatabaseManager& db);

    V<City> findAll(); //get all cities from db

  private:
    City mapRowToEntity(const std::vector<std::string>& row);    //converts a database row (vector of strings) to a City object
};

#endif
#ifndef FOOD_REPOSITORY_HPP
#define FOOD_REPOSITORY_HPP

#include "../header.hpp"
#include "../entities/Food.hpp"

class DatabaseManager;

class FoodRepository {
  private:
    DatabaseManager& database;

  public:
    FoodRepository(DatabaseManager& db);

    V<Food> findAll();  // Get all foods from the database
    V<Food> findByCityId(int cityId);    // Get foods for a specific city (filtered by city ID)

  private:
    Food mapRowToEntity(const std::vector<std::string>& row);  //converts a database row (vector of strings) to a Food object

};


#endif
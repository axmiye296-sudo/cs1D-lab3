#ifndef FOOD_REPOSITORY_HPP
#define FOOD_REPOSITORY_HPP

#include "../header.hpp"
#include "../entities/Food.hpp"


class FoodRepository {
  private:
    DatabaseManager& database;

  public:
    FoodRepository(DatabaseManager& db);

    V<Food> findAll();  // Get all foods from the database
    V<Food> findByCityId(int cityId);    // Get foods for a specific city (filtered by city ID)
    
    // Admin methods for database modifications
    bool insert(const Food& food);       // Add new food to database
    bool update(const Food& food);       // Update existing food in database
    bool deleteById(int foodId);         // Delete food from database
    Food* findById(int foodId);          // Find specific food by ID

  private:
    Food mapRowToEntity(const std::vector<std::string>& row);  //converts a database row (vector of strings) to a Food object

};


#endif
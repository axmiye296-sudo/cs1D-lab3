#ifndef FOODREPOSITORY_HPP
#define FOODREPOSITORY_HPP

#include "../header.hpp"
#include "../entities/Food.hpp"

class DatabaseManager;

class FoodRepository {
private:
    DatabaseManager& database;
    Food mapRowToEntity(const std::vector<std::string>& row); 
    
public:
    FoodRepository(DatabaseManager& db);// 
    
    V<Food> findAll(); // get all foods from the database
    V<Food> findByCityId(int cityId); // get foods for a specific city
};
#endif // FOODREPOSITORY_HPP
#ifndef FOODSERVICE_HPP
#define FOODSERVICE_HPP

#include "../header.hpp"
#include "../entities/Food.hpp"

class FoodRepository;

class FoodService {
private:
    FoodRepository& foodRepo;

public:
    FoodService(FoodRepository& foodRepo);
    V<Food> getAllFoods();                 // Get all foods from the database
    V<Food> getFoodsByCityId(int cityId);  // Get foods for a specific city
    void displayAllFoods();                // Display all foods on screen
    void displayFoodsByCityId(int cityId); // Display foods for a specific city

private:
    void displayFood(const Food& food);    // Displays one food
};

#endif // FOODSERVICE_HPP

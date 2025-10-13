#ifndef FOOD_SERVICE_HPP
#define FOOD_SERVICE_HPP

#include "../header.hpp"
#include "../entities/Food.hpp"

class FoodRepository;

class FoodService {
private:
    FoodRepository& foodRepo;

public:
    FoodService(FoodRepository& foodRepo);    //takes food repo and stores it

    V<Food> getAllFoods();                    // Get all foods from the database
    V<Food> getFoodsByCityId(int cityId);     // Get foods for a specific city

    void displayAllFoods();                   // Display all foods on screen
    void displayFoodsByCityId(int cityId);    // Display foods for a specific city

private:

    void displayFood(const Food& food);        // displays one food

};

#endif
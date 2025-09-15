#include "../include/services/FoodService.hpp"
#include "../include/repositories/FoodRepository.hpp"
#include <iostream>
/**
 * @file FoodService.cpp
 * @brief Implementation of the FoodService class for managing food-related operations.
 * 
 * This service provides methods to retrieve and display food items from the database,
 * either all foods or filtered by city ID. It interacts with the FoodRepository to
 * perform data access operations.
 * 
 * Key functionalities include:
 * - Retrieving all food items
 * - Retrieving food items by city ID
 * - Displaying food items in a formatted manner
 * 
 * The service ensures separation of concerns by handling business logic while
 * delegating data access to the repository layer.
 */

// Constructor
FoodService::FoodService(FoodRepository& foodRepo) : foodRepo(foodRepo) {}

// Get all foods from the repository
std::vector<Food> FoodService::getAllFoods() {
    return foodRepo.findAll();
}

// Get foods filtered by city ID
std::vector<Food> FoodService::getFoodsByCityId(int cityId) {
    return foodRepo.findByCityId(cityId);
}

// Display all foods
void FoodService::displayAllFoods() {
    std::vector<Food> foods = getAllFoods();
    for (const auto& food : foods) {
        displayFood(food);
    }
}

// Display foods for a specific city
void FoodService::displayFoodsByCityId(int cityId) {
    std::vector<Food> foods = getFoodsByCityId(cityId);
    for (const auto& food : foods) {
        displayFood(food);
    }
}

// Helper: Display a single food
void FoodService::displayFood(const Food& food) {
    food.print();  // calls Food::print() from Food.cpp
}

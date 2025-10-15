/**
 * @file FoodService.cpp
 * @brief Implementation of FoodService class for food-related operations
 */

#include "../../include/services/FoodService.hpp"
#include "../../include/repositories/FoodRepository.hpp"
#include <iostream>

// ============================================================================
// CONSTRUCTOR
// ============================================================================

/**
 * @brief Constructor implementation
 * @param foodRepo Reference to FoodRepository instance
 * 
 * Initializes the food service with a food repository.
 * All food operations will be performed through this repository.
 */
FoodService::FoodService(FoodRepository& foodRepo) : foodRepo(foodRepo) {
}

// ============================================================================
// PUBLIC METHODS
// ============================================================================

/**
 * @brief Get all foods from the database
 * @return Vector containing all Food objects
 * 
 * Retrieves all food items from the database through the food repository.
 * This method acts as a service layer wrapper around the repository.
 */
V<Food> FoodService::getAllFoods() {
    V<Food> foods = foodRepo.findAll();  // Call the FoodRepository method to get all foods
                                         // This returns a V<Food> container with all foods from the database
    return foods;                        // Return all the Food objects we found
}

/**
 * @brief Get foods for a specific city
 * @param cityId The ID of the city to get foods for
 * @return Vector containing Food objects for the specified city
 * 
 * Retrieves all food recommendations associated with a specific city.
 * This method acts as a service layer wrapper around the repository.
 */
V<Food> FoodService::getFoodsByCityId(int cityId) {
    V<Food> foods = foodRepo.findByCityId(cityId);  // Call the FoodRepository method to get foods for a specific city
                                                    // This returns a V<Food> container with foods for the specified city
    return foods;  // Return all the Food objects we found for this city
}

/**
 * @brief Display all foods in a formatted view
 * 
 * Shows all food items from the database in a nicely formatted display.
 * Creates a header with decorative borders and lists all foods with their details.
 */
void FoodService::displayAllFoods() {
    // Display header - create a nice looking title
    std::cout << "\n" << std::string(50, '=') << std::endl;
    // \n = new line
    // std::string(50, '=') = create a string with 50 equal signs
    // std::endl = end the line and move to next line

    std::cout << "                    ALL FOODS" << std::endl;
    // Print the title centered (with spaces to center it)

    std::cout << std::string(50, '=') << std::endl;
    // Print another line of equal signs

    // Get all foods from the database
    V<Food> foods = getAllFoods();  // Call our getAllFoods() method to get all foods
                                    // This returns a V<Food> container with all foods

    // Display each food
    for (int i = 0; i < foods.size(); i++) {
        // Loop through each food we got from the database
        // i starts at 0 and goes up to foods.size() - 1

        Food food = foods[i];  // Get the current food from the container
                               // foods[i] gets the food at position i

        displayFood(food);     // Display this food
                               // Call our helper method to show the food
    }

    // Display footer - create a nice looking ending
    std::cout << std::string(50, '=') << std::endl;
    // Print another line of equal signs
}

/**
 * @brief Display foods for a specific city
 * @param cityId The ID of the city to display foods for
 * 
 * Shows all food recommendations for a specific city in a formatted display.
 * Creates a header with the city ID and lists all associated foods with their details.
 */
void FoodService::displayFoodsByCityId(int cityId) {
    // Display header - create a nice looking title
    std::cout << "\n" << std::string(50, '=') << std::endl;
    // \n = new line
    // std::string(50, '=') = create a string with 50 equal signs
    // std::endl = end the line and move to next line

    std::cout << "                FOODS FOR CITY ID: " << cityId << std::endl;
    // Print the title with the city ID

    std::cout << std::string(50, '=') << std::endl;
    // Print another line of equal signs

    // Get foods for this city from the database
    V<Food> foods = getFoodsByCityId(cityId);  // Call our getFoodsByCityId() method to get foods for this city
                                               // This returns a V<Food> container with foods for the specified city

    // Display each food
    for (int i = 0; i < foods.size(); i++) {
        // Loop through each food we got from the database
        // i starts at 0 and goes up to foods.size() - 1

        Food food = foods[i];  // Get the current food from the container
                               // foods[i] gets the food at position i

        displayFood(food);     // Display this food
                               // Call our helper method to show the food
    }

    // Display footer - create a nice looking ending
    std::cout << std::string(50, '=') << std::endl;
    // Print another line of equal signs
}

// ============================================================================
// HELPER METHODS
// ============================================================================

/**
 * @brief Display a single food item
 * @param food The Food object to display
 * 
 * Shows the details of a single food item in a simple format.
 * Displays the food name and price.
 */
void FoodService::displayFood(const Food& food) {
    // Display food information
    std::cout << food.getName()
              << ", Price: €" << food.getPrice() << std::endl;
    // Example output: "ID: 1, Name: Croissant, City ID: 1, Price: €2.5"
}
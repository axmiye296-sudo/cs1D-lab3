#include "../../include/services/FoodService.hpp"
#include "../../include/repositories/FoodRepository.hpp"
#include <iostream>

FoodService::FoodService(FoodRepository& foodRepo) : foodRepo(foodRepo) {
}

// Method to get all foods from the database
V<Food> FoodService::getAllFoods() {
    V<Food> foods = foodRepo.findAll();  // Call the FoodRepository method to get all foods
                                         // This returns a V<Food> container with all foods from the database
    return foods;                        // Return all the Food objects we found
}

// Method to get foods for a specific city
V<Food> FoodService::getFoodsByCityId(int cityId) {
    V<Food> foods = foodRepo.findByCityId(cityId);  // Call the FoodRepository method to get foods for a specific city
                                                    // This returns a V<Food> container with foods for the specified city
    return foods;  // Return all the Food objects we found for this city
}

// Method to display all foods on screen
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

// Method to display foods for a specific city
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

// Helper method - displays one food
void FoodService::displayFood(const Food& food) {
    // Display food information
    std::cout << "ID: " << food.getId() << ", Name: " << food.getName()
              << ", City ID: " << food.getCityId() << ", Price: €" << food.getPrice() << std::endl;
    // Example output: "ID: 1, Name: Croissant, City ID: 1, Price: €2.5"
}
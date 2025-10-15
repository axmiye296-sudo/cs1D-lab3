/**
 * @file FoodService.hpp
 * @brief Service class for Food business logic operations
 */

 #ifndef FOOD_SERVICE_HPP
 #define FOOD_SERVICE_HPP
 
 #include "../header.hpp"
 #include "../entities/Food.hpp"
 
 class FoodRepository;
 
 /**
  * @class FoodService
  * @brief Handles business logic operations for Food entities
  * 
  * The FoodService class provides high-level business operations
  * for food recommendations, including data retrieval and display functionality.
  * It acts as an intermediary between the API layer and the repository layer.
  */
 class FoodService {
 private:
     FoodRepository& foodRepo;  ///< Reference to FoodRepository for data access
 
 public:
     /**
      * @brief Constructor
      * @param foodRepo Reference to FoodRepository instance
      * 
      * Initializes the service with a repository for data access.
      */
     FoodService(FoodRepository& foodRepo);
 
     /**
      * @brief Get all foods from the repository
      * @return Vector containing all Food objects
      * 
      * Retrieves all food recommendations through the repository layer.
      */
     V<Food> getAllFoods();
     
     /**
      * @brief Get foods for a specific city
      * @param cityId The ID of the city
      * @return Vector containing Food objects for the specified city
      * 
      * Retrieves all food recommendations associated with a specific city.
      */
     V<Food> getFoodsByCityId(int cityId);
 
     /**
      * @brief Display all foods to the console
      * 
      * Prints information about all food recommendations in a formatted manner.
      * Used for console output and debugging purposes.
      */
     void displayAllFoods();
     
     /**
      * @brief Display foods for a specific city
      * @param cityId The ID of the city
      * 
      * Shows all food recommendations for the specified city.
      * Used for city-specific food recommendations.
      */
     void displayFoodsByCityId(int cityId);
 
 private:
     /**
      * @brief Display information for a single food item
      * @param food The Food object to display
      * 
      * Helper method to format and display information about
      * a single food item. Used internally by other display methods.
      */
     void displayFood(const Food& food);
 };
 
 #endif
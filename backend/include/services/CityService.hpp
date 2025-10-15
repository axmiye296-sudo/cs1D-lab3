/**
 * @file CityService.hpp
 * @brief Service class for City business logic operations
 */

 #ifndef CITY_SERVICE_HPP
 #define CITY_SERVICE_HPP
 
 #include "../header.hpp"
 #include "../entities/City.hpp"
 
 class CityRepository;
 class FoodService;
 
 /**
  * @class CityService
  * @brief Handles business logic operations for City entities
  * 
  * The CityService class provides high-level business operations
  * for cities, including data retrieval and display functionality.
  * It acts as an intermediary between the API layer and the repository layer.
  */
 class CityService {
 private:
     CityRepository& cityRepo; ///< Reference to CityRepository for data access
 
 public:
     /**
      * @brief Constructor
      * @param cityRepo Reference to CityRepository instance
      * 
      * Initializes the service with a repository for data access.
      */
     CityService(CityRepository& cityRepo);
 
     /**
      * @brief Get all cities from the repository
      * @return Vector containing all City objects
      * 
      * Retrieves all cities through the repository layer.
      */
     V<City> getAllCities();
     
     /**
      * @brief Display all cities to the console
      * 
      * Prints information about all cities in a formatted manner.
      * Used for console output and debugging purposes.
      */
     void displayAllCities();
     
     /**
      * @brief Display cities with their associated food recommendations
      * @param foodService Reference to FoodService for food data
      * 
      * Shows all cities along with their food recommendations.
      * This method combines city and food data for comprehensive display.
      */
     void displayCitiesWithFood(FoodService& foodService);
 
 private:
     /**
      * @brief Display information for a single city
      * @param city The City object to display
      * 
      * Helper method to format and display information about
      * a single city. Used internally by other display methods.
      */
     void displayCity(const City& city);
 };
 
 #endif
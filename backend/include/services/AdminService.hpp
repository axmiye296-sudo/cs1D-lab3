/**
 * @file AdminService.hpp
 * @brief Service class for administrative operations and data management
 */

 #ifndef ADMIN_SERVICE_HPP
 #define ADMIN_SERVICE_HPP
 
 #include "../entities/Admin.hpp"
 #include "../entities/City.hpp"
 #include "../entities/Food.hpp"
 #include "../entities/CityDistance.hpp"
 #include "../repositories/CityRepository.hpp"
 #include "../repositories/FoodRepository.hpp"
 #include "../repositories/CityDistanceRepository.hpp"
 #include <vector>
 
 /**
  * @class AdminService
  * @brief Handles administrative operations and data management
  * 
  * The AdminService class provides high-level administrative functionality
  * for managing cities, foods, and city distances. It requires admin authentication
  * for most operations and acts as a business logic layer for administrative tasks.
  */
 class AdminService {
 private:
     Admin currentAdmin;                    ///< Currently logged-in admin user
     CityRepository& cityRepo;              ///< Repository for city operations
     FoodRepository& foodRepo;              ///< Repository for food operations
     CityDistanceRepository& cityDistanceRepo; ///< Repository for distance operations
 
 public:
     /**
      * @brief Constructor
      * @param cityRepo Reference to CityRepository instance
      * @param foodRepo Reference to FoodRepository instance
      * @param cityDistanceRepo Reference to CityDistanceRepository instance
      * 
      * Initializes the service with required repositories.
      */
     AdminService(CityRepository& cityRepo, FoodRepository& foodRepo, CityDistanceRepository& cityDistanceRepo);
 
     // Admin authentication
     /**
      * @brief Authenticate admin user
      * @param username The admin username
      * @param password The admin password
      * @return True if authentication successful, false otherwise
      * 
      * Attempts to log in an admin user with the provided credentials.
      */
     bool loginAdmin(const std::string& username, const std::string& password);
     
     /**
      * @brief Log out the current admin
      * 
      * Logs out the currently authenticated admin user.
      */
     void logoutAdmin();
     
     /**
      * @brief Check if admin is currently logged in
      * @return True if admin is logged in, false otherwise
      * 
      * Verifies the current authentication status.
      */
     bool isAdminLoggedIn() const;
 
     // City management functions (admin only)
     /**
      * @brief Add a new city
      * @param cityName The name of the city to add
      * @return True if city added successfully, false otherwise
      * 
      * Adds a new city to the database. Requires admin authentication.
      */
     bool addNewCity(const std::string& cityName);
     
     /**
      * @brief Update a city's name
      * @param cityId The ID of the city to update
      * @param newName The new name for the city
      * @return True if update successful, false otherwise
      * 
      * Updates the name of an existing city. Requires admin authentication.
      */
     bool updateCityName(int cityId, const std::string& newName);
     
     /**
      * @brief Delete a city
      * @param cityId The ID of the city to delete
      * @return True if deletion successful, false otherwise
      * 
      * Removes a city from the database. Requires admin authentication.
      */
     bool deleteCity(int cityId);
     
     /**
      * @brief Display all cities
      * 
      * Shows all cities in the database in a formatted display.
      * Requires admin authentication.
      */
     void displayAllCities();
 
     // Food management functions (admin only)
     /**
      * @brief Add food to a city
      * @param cityId The ID of the city
      * @param foodName The name of the food item
      * @param price The price of the food item
      * @return True if food added successfully, false otherwise
      * 
      * Adds a new food recommendation to a specific city.
      * Requires admin authentication.
      */
     bool addFoodToCity(int cityId, const std::string& foodName, double price);
     
     /**
      * @brief Update food price
      * @param foodId The ID of the food item
      * @param newPrice The new price for the food item
      * @return True if update successful, false otherwise
      * 
      * Updates the price of an existing food item.
      * Requires admin authentication.
      */
     bool updateFoodPrice(int foodId, double newPrice);
     
     /**
      * @brief Update food name
      * @param foodId The ID of the food item
      * @param newName The new name for the food item
      * @return True if update successful, false otherwise
      * 
      * Updates the name of an existing food item.
      * Requires admin authentication.
      */
     bool updateFoodName(int foodId, const std::string& newName);
     
     /**
      * @brief Delete a food item
      * @param foodId The ID of the food item to delete
      * @return True if deletion successful, false otherwise
      * 
      * Removes a food item from the database.
      * Requires admin authentication.
      */
     bool deleteFood(int foodId);
     
     /**
      * @brief Display all foods
      * 
      * Shows all food items in the database in a formatted display.
      * Requires admin authentication.
      */
     void displayAllFoods();
     
     /**
      * @brief Display foods for a specific city
      * @param cityId The ID of the city
      * 
      * Shows all food items associated with a specific city.
      * Requires admin authentication.
      */
     void displayFoodsByCityId(int cityId);
 
     // Data access methods
     /**
      * @brief Get all cities
      * @return Vector containing all City objects
      * 
      * Retrieves all cities from the database.
      */
     V<City> getAllCities();
     
     /**
      * @brief Get all foods
      * @return Vector containing all Food objects
      * 
      * Retrieves all food items from the database.
      */
     V<Food> getAllFoods();
     
     // File processing functions
     /**
      * @brief Process city data from file
      * @param fileContent The content of the data file
      * @return True if processing successful, false otherwise
      * 
      * Processes city data from a file format and adds it to the database.
      * Requires admin authentication.
      */
     bool processCityDataFile(const std::string& fileContent);
     
     /**
      * @brief Process cities from JSON file
      * @param jsonContent The JSON content to process
      * @return True if processing successful, false otherwise
      * 
      * Processes city data from JSON format and adds it to the database.
      * Requires admin authentication.
      */
     bool processCitiesJsonFile(const std::string& jsonContent);
     
     /**
      * @brief Add city with associated data from file
      * @param cityName The name of the city
      * @param foods Vector of food name-price pairs
      * @param distances Vector of city name-distance pairs
      * @return True if addition successful, false otherwise
      * 
      * Adds a city along with its associated foods and distances.
      * Requires admin authentication.
      */
     bool addCityFromFileData(const std::string& cityName, 
                            const std::vector<std::pair<std::string, double>>& foods,
                            const std::vector<std::pair<std::string, int>>& distances);
 
     // Permission checking
     /**
      * @brief Check if admin has permission to perform operations
      * @return True if admin is logged in and has permission, false otherwise
      * 
      * Verifies that an admin is currently logged in before allowing
      * administrative operations.
      */
     bool checkAdminPermission() const;
 };
 
 #endif
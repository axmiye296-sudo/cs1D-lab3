/**
 * This file is the header for the AdminServices entity containing function
 * signatures.
 * For managing cities and foods in the database (add/update). Does not handle
 * admin login/logout - that is in Admin entity.
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

class AdminService {
private:
    Admin currentAdmin;
    CityRepository& cityRepo;
    FoodRepository& foodRepo;
    CityDistanceRepository& cityDistanceRepo;

public:
    // Constructor
    AdminService(CityRepository& cityRepo, FoodRepository& foodRepo, CityDistanceRepository& cityDistanceRepo);

    // Admin login/logout
    bool loginAdmin(const std::string& username, const std::string& password);
    void logoutAdmin();
    bool isAdminLoggedIn() const;

    // City management functions (only if admin is logged in)
    bool addNewCity(const std::string& cityName);
    bool updateCityName(int cityId, const std::string& newName);
    bool deleteCity(int cityId);
    void displayAllCities();

    // Food management functions (only if admin is logged in)
    bool addFoodToCity(int cityId, const std::string& foodName, double price);
    bool updateFoodPrice(int foodId, double newPrice);
    bool updateFoodName(int foodId, const std::string& newName);
    bool deleteFood(int foodId);
    void displayAllFoods();
    void displayFoodsByCityId(int cityId);

    // repo getters
    V<City> getAllCities();
    V<Food> getAllFoods();
    
    // File upload and processing functions
    bool processCityDataFile(const std::string& fileContent);
    bool processCitiesJsonFile(const std::string& jsonContent);
    bool addCityFromFileData(const std::string& cityName, 
                           const std::vector<std::pair<std::string, double>>& foods,
                           const std::vector<std::pair<std::string, int>>& distances);

    // Helper function to check admin permissions
    bool checkAdminPermission() const;
};

#endif
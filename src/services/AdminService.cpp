/**
 * This file contains admin service methods for managing cities and foods
 * Changes will be saved to database so if testing please make sure to delete
 */
#include "../../include/services/AdminService.hpp"
#include <iostream>

// Constructor
AdminService::AdminService(CityRepository& cityRepo, FoodRepository& foodRepo) 
    : cityRepo(cityRepo), foodRepo(foodRepo) {
    // Create a default admin for testing (username: admin, password: password)
    currentAdmin = Admin(1, "admin", "password");
}

// Admin login
bool AdminService::loginAdmin(const std::string& username, const std::string& password) {
    return currentAdmin.login(username, password);
}

// Admin logout
void AdminService::logoutAdmin() {
    currentAdmin.logout();
}

// Check if admin is logged in
bool AdminService::isAdminLoggedIn() const {
    return currentAdmin.getIsLoggedIn();
}

// Check admin permission before allowing operations
bool AdminService::checkAdminPermission() const {
    if (!isAdminLoggedIn()) {
        std::cout << "Access denied! Please login as admin first." << std::endl;
        return false;
    }
    return true;
}

// Add a new city (admin only)
bool AdminService::addNewCity(const std::string& cityName) {
    if (!checkAdminPermission()) {
        return false;
    }

    std::cout << "Adding new city: " << cityName << std::endl;

    // Get all existing cities to find the next available ID
    V<City> allCities = cityRepo.findAll();
    int newId = allCities.size() + 1;

    // Create new city (only id and name available in current City class)
    City newCity(newId, cityName);
    
    // Use the new database insert method
    if (cityRepo.insert(newCity)) {
        std::cout << "City successfully added: " << cityName << " (ID: " << newId << ")" << std::endl;
        return true;
    } else {
        std::cout << "Error: Failed to add city to database!" << std::endl;
        return false;
    }
}

// Update city name (admin only)
bool AdminService::updateCityName(int cityId, const std::string& newName) {
    if (!checkAdminPermission()) {
        return false;
    }

    std::cout << "\nUpdating city ID " << cityId << " to: " << newName << std::endl;
    
    // First, find the city to make sure it exists and get its current data
    City* existingCity = cityRepo.findById(cityId);
    if (!existingCity) {
        std::cout << "City with ID " << cityId << " not found!" << std::endl;
        return false;
    }
    
    // Create updated city with new name
    City updatedCity(cityId, newName);
    
    // Use the database update method
    if (cityRepo.update(updatedCity)) {
        std::cout << "Successfully updated city: " << existingCity->getName() << " to " << newName << std::endl;
        delete existingCity; // Clean up
        return true;
    } else {
        std::cout << "Error: Failed to update city in database!" << std::endl;
        delete existingCity; // Clean up
        return false;
    }
}

// Display all cities
void AdminService::displayAllCities() {
    if (!checkAdminPermission()) {
        return;
    }

    std::cout << "\nAll Cities (Admin View):" << std::endl;
    std::cout << "=============================" << std::endl;
    
    V<City> allCities = cityRepo.findAll();
    
    if (allCities.empty()) {
        std::cout << "No cities found." << std::endl;
        return;
    }
    
    for (const auto& city : allCities) {
        std::cout << "ID: " << city.getId() 
                  << " | Name: " << city.getName() << std::endl;
    }
}

// Add food to a city (admin only)
bool AdminService::addFoodToCity(int cityId, const std::string& foodName, double price) {
    if (!checkAdminPermission()) {
        return false;
    }

    std::cout << "\nAdding food '" << foodName << "' ($" << price 
              << ") to city ID " << cityId << std::endl;

    // Check if city exists
    City* existingCity = cityRepo.findById(cityId);
    if (!existingCity) {
        std::cout << "City with ID " << cityId << " not found!" << std::endl;
        return false;
    }
    
    // Get all foods to find the next available ID
    V<Food> allFoods = foodRepo.findAll();
    int newId = allFoods.size() + 1;
    
    // Create new food
    Food newFood(newId, foodName, cityId, price);
    
    // Use the database insert method
    if (foodRepo.insert(newFood)) {
        std::cout << "Successfully added food '" << foodName << "' to " << existingCity->getName() << std::endl;
        delete existingCity; // Clean up
        return true;
    } else {
        std::cout << "Error: Failed to add food to database!" << std::endl;
        delete existingCity; // Clean up
        return false;
    }
}

// Update food price (admin only)
bool AdminService::updateFoodPrice(int foodId, double newPrice) {
    if (!checkAdminPermission()) {
        return false;
    }

    std::cout << "\nUpdating price for food ID " << foodId << " to $" << newPrice << std::endl;
    
    // First, find the food to make sure it exists and get its current data
    Food* existingFood = foodRepo.findById(foodId);
    if (!existingFood) {
        std::cout << "Food with ID " << foodId << " not found!" << std::endl;
        return false;
    }
    
    // Create updated food with new price
    Food updatedFood(existingFood->getId(), existingFood->getName(), existingFood->getCityId(), newPrice);
    
    // Use the database update method
    if (foodRepo.update(updatedFood)) {
        std::cout << "Food price updated successfully!" << std::endl;
        delete existingFood; // Clean up
        return true;
    } else {
        std::cout << "Error: Failed to update food price in database!" << std::endl;
        delete existingFood; // Clean up
        return false;
    }
}

// Update food name (admin only)
bool AdminService::updateFoodName(int foodId, const std::string& newName) {
    if (!checkAdminPermission()) {
        return false;
    }

    std::cout << "\nUpdating name for food ID " << foodId << " to: " << newName << std::endl;
    
    // First, find the food to make sure it exists and get its current data
    Food* existingFood = foodRepo.findById(foodId);
    if (!existingFood) {
        std::cout << "Food with ID " << foodId << " not found!" << std::endl;
        return false;
    }
    
    // Create updated food with new name
    Food updatedFood(existingFood->getId(), newName, existingFood->getCityId(), existingFood->getPrice());
    
    // Use the database update method
    if (foodRepo.update(updatedFood)) {
        std::cout << "Food name updated successfully!" << std::endl;
        delete existingFood; // Clean up
        return true;
    } else {
        std::cout << "Error: Failed to update food name in database!" << std::endl;
        delete existingFood; // Clean up
        return false;
    }
}

// Delete city (admin only)
bool AdminService::deleteCity(int cityId) {
    if (!checkAdminPermission()) {
        return false;
    }

    std::cout << "\nDeleting city ID " << cityId << std::endl;
    
    // First, check if city exists
    City* existingCity = cityRepo.findById(cityId);
    if (!existingCity) {
        std::cout << "City with ID " << cityId << " not found!" << std::endl;
        return false;
    }
    
    std::string cityName = existingCity->getName();
    delete existingCity; // Clean up
    
    // Use the database delete method
    if (cityRepo.deleteById(cityId)) {
        std::cout << "Successfully deleted city: " << cityName << std::endl;
        return true;
    } else {
        std::cout << "Error: Failed to delete city from database!" << std::endl;
        return false;
    }
}

// Delete food (admin only)
bool AdminService::deleteFood(int foodId) {
    if (!checkAdminPermission()) {
        return false;
    }

    std::cout << "\nDeleting food ID " << foodId << std::endl;
    
    // First, check if food exists
    Food* existingFood = foodRepo.findById(foodId);
    if (!existingFood) {
        std::cout << "Food with ID " << foodId << " not found!" << std::endl;
        return false;
    }
    
    std::string foodName = existingFood->getName();
    delete existingFood; // Clean up
    
    // Use the database delete method
    if (foodRepo.deleteById(foodId)) {
        std::cout << "Successfully deleted food: " << foodName << std::endl;
        return true;
    } else {
        std::cout << "Error: Failed to delete food from database!" << std::endl;
        return false;
    }
}

// Display all foods (admin only)
void AdminService::displayAllFoods() {
    if (!checkAdminPermission()) {
        return;
    }

    std::cout << "\nAll Foods (Admin View):" << std::endl;
    std::cout << "===========================" << std::endl;
    
    V<Food> allFoods = foodRepo.findAll();
    
    if (allFoods.empty()) {
        std::cout << "No foods found." << std::endl;
        return;
    }
    
    for (const auto& food : allFoods) {
        std::cout << "ID: " << food.getId() 
                  << " | Name: " << food.getName() 
                  << " | Price: $" << food.getPrice()
                  << " | City ID: " << food.getCityId() << std::endl;
    }
}

// Display foods for a specific city (admin only)
void AdminService::displayFoodsForCity(int cityId) {
    if (!checkAdminPermission()) {
        return;
    }

    std::cout << "\nFoods for City ID " << cityId << ":" << std::endl;
    std::cout << "==============================" << std::endl;
    
    V<Food> cityFoods = foodRepo.findByCityId(cityId);
    
    if (cityFoods.empty()) {
        std::cout << "No foods found for this city." << std::endl;
        return;
    }
    
    for (const auto& food : cityFoods) {
        std::cout << "ID: " << food.getId() 
                  << " | Name: " << food.getName() 
                  << " | Price: $" << food.getPrice() << std::endl;
    }
}
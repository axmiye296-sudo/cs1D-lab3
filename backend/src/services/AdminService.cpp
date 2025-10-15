/**
 * This file contains admin service methods for managing cities and foods
 * Changes will be saved to database so if testing please make sure to delete
 */
#include "../../include/services/AdminService.hpp"
#include "crow/crow_all.h"
#include <iostream>
#include <sstream>
#include <string>
#include <set>

// Constructor
AdminService::AdminService(CityRepository& cityRepo, FoodRepository& foodRepo, CityDistanceRepository& cityDistanceRepo) 
    : cityRepo(cityRepo), foodRepo(foodRepo), cityDistanceRepo(cityDistanceRepo) {
    // Create a default admin for testing (username: admin, password: password)
    currentAdmin = Admin("admin", "password");
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

    // Get all existing cities and find the smallest available ID
    V<City> allCities = cityRepo.findAll();
    
    // Create a set of existing IDs
    std::set<int> existingIds;
    for (const auto& city : allCities) {
        existingIds.insert(city.getId());
    }
    
    // Find the smallest available ID (starting from 1)
    int newId = 1;
    while (existingIds.count(newId) > 0) {
        newId++;
    }

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

// Display all cities (admin or user)
void AdminService::displayAllCities() {
    
    std::cout << "\nAll Cities " << std::endl;
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
    
    // Get all foods and check if this food already exists for this city
    V<Food> allFoods = foodRepo.findAll();
    
    // Check for duplicate food (same name and city)
    for (const auto& food : allFoods) {
        if (food.getCityId() == cityId && food.getName() == foodName) {
            std::cout << "⚠️  Food '" << foodName << "' already exists for " << existingCity->getName() 
                      << " (ID: " << food.getId() << "), skipping duplicate." << std::endl;
            delete existingCity;
            return true; // Return true since the food exists (not an error)
        }
    }
    
    // Create a set of existing food IDs to find smallest available ID
    std::set<int> existingIds;
    for (const auto& food : allFoods) {
        existingIds.insert(food.getId());
    }
    
    // Find the smallest available ID (starting from 1)
    int newId = 1;
    while (existingIds.count(newId) > 0) {
        newId++;
    }
    
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

// Display all foods (admin or user)
void AdminService::displayAllFoods() {
   
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

// Display foods for a specific city (admin or user)
void AdminService::displayFoodsByCityId(int cityId) {

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
V<Food> AdminService::getAllFoods() {
    return foodRepo.findAll();
}
V<City> AdminService::getAllCities() {
    return cityRepo.findAll();
}

// Process city data from uploaded file
bool AdminService::processCityDataFile(const std::string& fileContent) {
    if (!checkAdminPermission()) {
        std::cout << "Error: Admin permission required!" << std::endl;
        return false;
    }

    std::cout << "🔄 Processing city data file..." << std::endl;
    
    std::stringstream ss(fileContent);
    std::string line;
    std::string cityName;
    std::vector<std::pair<std::string, double>> foods;
    std::vector<std::pair<std::string, int>> distances;
    
    bool readingFoods = false;
    bool readingDistances = false;
    
    while (std::getline(ss, line)) {
        // Trim whitespace
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);
        
        if (line.empty() || line[0] == '#') continue; // Skip empty lines and comments
        
        if (line.find("CITY:") == 0) {
            cityName = line.substr(5);
            cityName.erase(0, cityName.find_first_not_of(" \t"));
            readingFoods = false;
            readingDistances = false;
        }
        else if (line == "FOODS:") {
            readingFoods = true;
            readingDistances = false;
        }
        else if (line == "DISTANCES:") {
            readingFoods = false;
            readingDistances = true;
        }
        else if (readingFoods && !line.empty()) {
            // Parse food: "FoodName,Price"
            size_t commaPos = line.find(',');
            if (commaPos != std::string::npos) {
                std::string foodName = line.substr(0, commaPos);
                double price = std::stod(line.substr(commaPos + 1));
                foods.push_back({foodName, price});
            }
        }
        else if (readingDistances && !line.empty()) {
            // Parse distance: "CityName,Distance"
            size_t commaPos = line.find(',');
            if (commaPos != std::string::npos) {
                std::string toCityName = line.substr(0, commaPos);
                int distance = std::stoi(line.substr(commaPos + 1));
                distances.push_back({toCityName, distance});
            }
        }
    }
    
    if (cityName.empty()) {
        std::cout << "❌ Error: No city name found in file!" << std::endl;
        return false;
    }
    
    return addCityFromFileData(cityName, foods, distances);
}

// Add city with all related data
bool AdminService::addCityFromFileData(const std::string& cityName, 
                                     const std::vector<std::pair<std::string, double>>& foods,
                                     const std::vector<std::pair<std::string, int>>& distances) {
    if (!checkAdminPermission()) {
        return false;
    }
    
    std::cout << "📍 Adding city: " << cityName << std::endl;
    
    // Check if city already exists
    V<City> allCities = cityRepo.findAll();
    int cityId = -1;
    bool cityExists = false;
    
    for (const auto& city : allCities) {
        if (city.getName() == cityName) {
            cityId = city.getId();
            cityExists = true;
            std::cout << "⚠️  City already exists: " << cityName << " (ID: " << cityId << "), updating foods and distances..." << std::endl;
            break;
        }
    }
    
    // 1. Add the city if it doesn't exist
    if (!cityExists) {
        if (!addNewCity(cityName)) {
            std::cout << "❌ Failed to add city: " << cityName << std::endl;
            return false;
        }
        
        // Get the newly created city to get its ID
        allCities = cityRepo.findAll();
        for (const auto& city : allCities) {
            if (city.getName() == cityName) {
                cityId = city.getId();
                break;
            }
        }
        
        if (cityId == -1) {
            std::cout << "❌ Error: Could not find newly created city!" << std::endl;
            return false;
        }
    }
    
    // 2. Add foods for this city
    std::cout << "🍽️  Adding " << foods.size() << " foods..." << std::endl;
    for (const auto& food : foods) {
        if (!addFoodToCity(cityId, food.first, food.second)) {
            std::cout << "⚠️  Warning: Failed to add food: " << food.first << std::endl;
        }
    }
    
    // 3. Add distances 
    std::cout << "🛣️  Processing " << distances.size() << " distances..." << std::endl;
    for (const auto& dist : distances) {
        // Find the destination city ID by name
        V<City> allCities = cityRepo.findAll();
        int toCityId = -1;
        for (const auto& city : allCities) {
            if (city.getName() == dist.first) {
                toCityId = city.getId();
                break;
            }
        }
        
        if (toCityId != -1) {
            // Create CityDistance object and save it
            CityDistance cityDistance(cityId, toCityId, dist.second);
            if (cityDistanceRepo.save(cityDistance)) {
                std::cout << "✅ Distance to " << dist.first << ": " << dist.second << "km (saved)" << std::endl;
            } else {
                std::cout << "❌ Failed to save distance to " << dist.first << std::endl;
            }
        } else {
            std::cout << "⚠️  Warning: Destination city '" << dist.first << "' not found for distance" << std::endl;
        }
    }
    
    std::cout << "✅ Successfully added city: " << cityName << " with all data!" << std::endl;
    return true;
}

// Process JSON file with multiple cities
bool AdminService::processCitiesJsonFile(const std::string& jsonContent) {
    if (!checkAdminPermission()) {
        return false;
    }
    
    std::cout << "📄 Processing JSON cities data..." << std::endl;
    
    try {
        // Parse JSON using Crow's JSON parser
        auto jsonData = crow::json::load(jsonContent);
        if (!jsonData) {
            std::cout << "❌ Error: Invalid JSON format!" << std::endl;
            return false;
        }
        
        if (!jsonData.has("cities")) {
            std::cout << "❌ Error: JSON must have 'cities' array!" << std::endl;
            return false;
        }
        
        auto citiesArray = jsonData["cities"];
        if (citiesArray.t() != crow::json::type::List) {
            std::cout << "❌ Error: 'cities' must be an array!" << std::endl;
            return false;
        }
        
        int successCount = 0;
        int totalCities = citiesArray.size();
        
        std::cout << "🏙️  Found " << totalCities << " cities to process..." << std::endl;
        
        // PASS 1: Add all cities and their foods (skip distances for now)
        std::cout << "\n📍 PASS 1: Creating cities and adding foods..." << std::endl;
        for (const auto& cityJson : citiesArray) {
            if (!cityJson.has("name")) {
                std::cout << "⚠️  Warning: Skipping city without name" << std::endl;
                continue;
            }
            
            std::string cityName = cityJson["name"].s();
            std::vector<std::pair<std::string, double>> foods;
            
            // Parse foods only
            if (cityJson.has("foods") && cityJson["foods"].t() == crow::json::type::List) {
                for (const auto& foodJson : cityJson["foods"]) {
                    if (foodJson.has("name") && foodJson.has("price")) {
                        std::string foodName = foodJson["name"].s();
                        double price = foodJson["price"].d();
                        foods.push_back({foodName, price});
                    }
                }
            }
            
            // Add the city with foods only (no distances yet)
            std::vector<std::pair<std::string, int>> emptyDistances;
            if (addCityFromFileData(cityName, foods, emptyDistances)) {
                successCount++;
                std::cout << "✅ Successfully created city: " << cityName << std::endl;
            } else {
                std::cout << "❌ Failed to create city: " << cityName << std::endl;
            }
        }
        
        // PASS 2: Add all distances now that all cities exist
        std::cout << "\n🛣️  PASS 2: Adding distances between cities..." << std::endl;
        int distanceCount = 0;
        for (const auto& cityJson : citiesArray) {
            if (!cityJson.has("name")) {
                continue;
            }
            
            std::string cityName = cityJson["name"].s();
            
            // Find the city ID
            V<City> allCities = cityRepo.findAll();
            int cityId = -1;
            for (const auto& city : allCities) {
                if (city.getName() == cityName) {
                    cityId = city.getId();
                    break;
                }
            }
            
            if (cityId == -1) {
                std::cout << "⚠️  Warning: Could not find city " << cityName << " for distance processing" << std::endl;
                continue;
            }
            
            // Parse and add distances
            if (cityJson.has("distances") && cityJson["distances"].t() == crow::json::type::List) {
                for (const auto& distJson : cityJson["distances"]) {
                    if (distJson.has("to") && distJson.has("distance")) {
                        std::string toCity = distJson["to"].s();
                        int distance = distJson["distance"].i();
                        
                        // Find the destination city ID
                        int toCityId = -1;
                        for (const auto& city : allCities) {
                            if (city.getName() == toCity) {
                                toCityId = city.getId();
                                break;
                            }
                        }
                        if (toCityId != -1) {
                            // Insert both directions: (from -> to) and (to -> from)
                            CityDistance cityDistance(cityId, toCityId, distance);
                            if (cityDistanceRepo.save(cityDistance)) {
                                distanceCount++;
                                std::cout << "✅ " << cityName << " → " << toCity << ": " << distance << "km" << std::endl;
                            }
                            // Check if reverse distance already exists, if not, insert it
                            int reverseDistance = cityDistanceRepo.getDistance(toCityId, cityId);
                            if (reverseDistance == -1) {
                                CityDistance reverseCityDistance(toCityId, cityId, distance);
                                if (cityDistanceRepo.save(reverseCityDistance)) {
                                    distanceCount++;
                                    std::cout << "✅ " << toCity << " → " << cityName << ": " << distance << "km (reverse)" << std::endl;
                                }
                            }
                        } else {
                            std::cout << "⚠️  Warning: Destination city '" << toCity << "' not found for distance from " << cityName << std::endl;
                        }
                    }
                }
            }
        }
        
        std::cout << "\n🎉 Processed " << successCount << "/" << totalCities << " cities successfully!" << std::endl;
        std::cout << "🛣️  Added " << distanceCount << " distances!" << std::endl;
        return successCount > 0;
        
    } catch (const std::exception& e) {
        std::cout << "❌ Error parsing JSON: " << e.what() << std::endl;
        return false;
    }
}
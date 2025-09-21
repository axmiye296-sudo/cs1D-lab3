/**
 * TripCity Data Access Implementation
 * Converts business operations to JSON database calls
 * Handles data validation and error checking
 */

#include "../include/tripCityDataAccess.hpp"
#include <iostream>

TripCityDataAccess::TripCityDataAccess(JsonDatabase& database) : db(database) {}

bool TripCityDataAccess::addCityToTrip(int tripId, int cityId, int visitOrder) {
    // Check if city already exists in trip
    if (cityExistsInTrip(tripId, cityId)) {
        std::cout << "City " << cityId << " already exists in trip " << tripId << std::endl;
        return false;
    }
    
    // Create data map
    std::map<std::string, std::string> data;
    data["trip_id"] = std::to_string(tripId);
    data["city_id"] = std::to_string(cityId);
    data["visit_order"] = std::to_string(visitOrder);
    
    // Insert into database
    int newId = db.insert("trip_cities", data);
    return newId > 0;
}

V<TripCity> TripCityDataAccess::getCitiesForTrip(int tripId) {
    V<TripCity> result;
    
    // Get all trip_cities for this trip
    V<std::map<std::string, std::string>> rows = db.selectWhere("trip_cities", "trip_id", std::to_string(tripId));
    
    // Convert to TripCity objects
    for (const auto& row : rows) {
        if (row.find("id") != row.end() && 
            row.find("trip_id") != row.end() && 
            row.find("city_id") != row.end() && 
            row.find("visit_order") != row.end()) {
            
            TripCity tripCity(
                std::stoi(row.at("id")),
                std::stoi(row.at("trip_id")),
                std::stoi(row.at("city_id")),
                std::stoi(row.at("visit_order"))
            );
            result.push_back(tripCity);
        }
    }
    
    return result;
}

bool TripCityDataAccess::removeCityFromTrip(int tripId, int cityId) {
    // Find the record
    V<std::map<std::string, std::string>> rows = db.selectWhere("trip_cities", "trip_id", std::to_string(tripId));
    
    for (const auto& row : rows) {
        if (row.find("city_id") != row.end() && 
            std::stoi(row.at("city_id")) == cityId) {
            
            int id = std::stoi(row.at("id"));
            return db.remove("trip_cities", id);
        }
    }
    
    return false;
}

bool TripCityDataAccess::updateVisitOrder(int tripId, int cityId, int newOrder) {
    // Find the record
    V<std::map<std::string, std::string>> rows = db.selectWhere("trip_cities", "trip_id", std::to_string(tripId));
    
    for (const auto& row : rows) {
        if (row.find("city_id") != row.end() && 
            std::stoi(row.at("city_id")) == cityId) {
            
            int id = std::stoi(row.at("id"));
            std::map<std::string, std::string> updateData;
            updateData["visit_order"] = std::to_string(newOrder);
            
            return db.update("trip_cities", id, updateData);
        }
    }
    
    return false;
}

bool TripCityDataAccess::cityExistsInTrip(int tripId, int cityId) {
    V<std::map<std::string, std::string>> rows = db.selectWhere("trip_cities", "trip_id", std::to_string(tripId));
    
    for (const auto& row : rows) {
        if (row.find("city_id") != row.end() && 
            std::stoi(row.at("city_id")) == cityId) {
            return true;
        }
    }
    
    return false;
}

int TripCityDataAccess::getNextVisitOrder(int tripId) {
    V<std::map<std::string, std::string>> rows = db.selectWhere("trip_cities", "trip_id", std::to_string(tripId));
    
    int maxOrder = 0;
    for (const auto& row : rows) {
        if (row.find("visit_order") != row.end()) {
            int order = std::stoi(row.at("visit_order"));
            maxOrder = std::max(maxOrder, order);
        }
    }
    
    return maxOrder + 1;
}

void TripCityDataAccess::printAllTripCities() {
    db.printTable("trip_cities");
}




#include "../../include/repositories/CityDistanceRepository.hpp"
#include "../../include/databaseManager.hpp"
#include <iostream>

CityDistanceRepository::CityDistanceRepository(DatabaseManager& db) : database(db) {}

V<CityDistance> CityDistanceRepository::findByFromCity(int fromCityId) {
    V<CityDistance> result;
    
    std::string query = "SELECT from_city_id, to_city_id, distance FROM city_distances WHERE from_city_id = " + 
                       std::to_string(fromCityId) + " ORDER BY distance ASC;";
    
    std::cout << "🔍 Executing query: " << query << std::endl;
    
    auto dbResult = database.executeSelect(query);
    
    for (const auto& row : dbResult) {
        if (row.size() >= 3) {
            result.push_back(mapRowToEntity(row));
        }
    }
    
    std::cout << "✅ Found " << result.size() << " distances from city " << fromCityId << std::endl;
    return result;
}

int CityDistanceRepository::getDistance(int fromCityId, int toCityId) {
    std::string query = "SELECT distance FROM city_distances WHERE from_city_id = " + 
                       std::to_string(fromCityId) + " AND to_city_id = " + std::to_string(toCityId) + ";";
    
    auto dbResult = database.executeSelect(query);
    
    if (!dbResult.empty() && !dbResult[0].empty()) {
        int distance = std::stoi(dbResult[0][0]);
        std::cout << "📏 Distance from " << fromCityId << " to " << toCityId << ": " << distance << " km" << std::endl;
        return distance;
    }
    
    std::cout << "❌ No distance found from " << fromCityId << " to " << toCityId << std::endl;
    return -1; // Distance not found
}

V<CityDistance> CityDistanceRepository::findAll() {
    V<CityDistance> result;
    
    std::string query = "SELECT from_city_id, to_city_id, distance FROM city_distances ORDER BY from_city_id, distance;";
    
    auto dbResult = database.executeSelect(query);
    
    for (const auto& row : dbResult) {
        if (row.size() >= 3) {
            result.push_back(mapRowToEntity(row));
        }
    }
    
    return result;
}

CityDistance CityDistanceRepository::mapRowToEntity(const std::vector<std::string>& row) {
    int fromCityId = std::stoi(row[0]);
    int toCityId = std::stoi(row[1]);
    int distance = std::stoi(row[2]);
    
    return CityDistance(fromCityId, toCityId, distance);
}

bool CityDistanceRepository::save(const CityDistance& cityDistance) {
    // Check if distance already exists
    int existingDistance = getDistance(cityDistance.getFromCityId(), cityDistance.getToCityId());
    
    if (existingDistance != -1) {
        // Update existing distance
        std::string updateQuery = "UPDATE city_distances SET distance = " + 
                                std::to_string(cityDistance.getDistance()) + 
                                " WHERE from_city_id = " + std::to_string(cityDistance.getFromCityId()) + 
                                " AND to_city_id = " + std::to_string(cityDistance.getToCityId()) + ";";
        
        std::cout << "🔄 Updating existing distance: " << updateQuery << std::endl;
        return database.executeInsert(updateQuery);
    } else {
        // Insert new distance
        std::string insertQuery = "INSERT INTO city_distances (from_city_id, to_city_id, distance) VALUES (" +
                                std::to_string(cityDistance.getFromCityId()) + ", " +
                                std::to_string(cityDistance.getToCityId()) + ", " +
                                std::to_string(cityDistance.getDistance()) + ");";
        
        std::cout << "➕ Inserting new distance: " << insertQuery << std::endl;
        return database.executeInsert(insertQuery);
    }
}




#include "../../include/repositories/TripCityRepository.hpp"
#include "../../include/databaseManager.hpp"
#include "../../include/entities/tripCities.hpp"
#include <sstream>
#include <stdexcept>

/**
*
 constructor:
    takes a reference for DatabaseManager
    stores the reference for database operations
    - uses the existing connection
*/
TripCityRepository::TripCityRepository(DatabaseManager& database) : db(database) {}

/**
* CRUD operations: create/update
 */
bool TripCityRepository::save(TripCity& tripCity) {
    if (!db.isConnected()) {
        return false;
    }
    
    try {
        if (tripCity.getId() == 0) {
            // Insert new record
            std::string query = buildInsertQuery(tripCity);
            int newId = db.executeInsert(query);
            
            if (newId > 0) {
                tripCity.setId(newId);
                return true;
            }
        } else {
            // Update existing record
            std::string query = buildUpdateQuery(tripCity);
            return db.executeUpdate(query);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error saving TripCity: " << e.what() << std::endl;
    }
    
    return false;
}
//read
bool TripCityRepository::load(int id, TripCity& tripCity) {
    if (!db.isConnected()) {
        return false;
    }
    
    try {
        std::string query = buildSelectQuery(id);
        V<std::vector<std::string>> result = db.executeSelect(query);
        
        if (result.size() > 0) {
            tripCity = mapRowToEntity(result[0]);
            return true;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error loading TripCity: " << e.what() << std::endl;
    }
    
    return false;
}
//delete
bool TripCityRepository::remove(int id) {
    if (!db.isConnected()) {
        return false;
    }
    
    try {
        std::string query = buildDeleteQuery(id);
        return db.executeDelete(query);
    } catch (const std::exception& e) {
        std::cerr << "Error removing TripCity: " << e.what() << std::endl;
    }
    
    return false;
}

//custom methods
V<TripCity> TripCityRepository::findAll() {
    V<TripCity> result;
    
    if (!db.isConnected()) {
        return result;
    }
    
    try {
        std::string query = buildSelectAllQuery();
        V<std::vector<std::string>> rows = db.executeSelect(query);
        
        for (size_t i = 0; i < rows.size(); i++) {
            result.push_back(mapRowToEntity(rows[i]));
        }
    } catch (const std::exception& e) {
        std::cerr << "Error finding all TripCities: " << e.what() << std::endl;
    }
    
    return result;
}

V<TripCity> TripCityRepository::findByTrip(int tripId) {
    V<TripCity> result;
    
    if (!db.isConnected()) {
        return result;
    }
    
    try {
        std::string query = buildSelectByTripQuery(tripId);
        V<std::vector<std::string>> rows = db.executeSelect(query);
        
        for (size_t i = 0; i < rows.size(); i++) {
            result.push_back(mapRowToEntity(rows[i]));
        }
    } catch (const std::exception& e) {
        std::cerr << "Error finding TripCities by trip: " << e.what() << std::endl;
    }
    
    return result;
}

V<TripCity> TripCityRepository::findByCity(int cityId) {
    V<TripCity> result;
    
    if (!db.isConnected()) {
        return result;
    }
    
    try {
        std::string query = buildSelectByCityQuery(cityId);
        V<std::vector<std::string>> rows = db.executeSelect(query);
        
        for (size_t i = 0; i < rows.size(); i++) {
            result.push_back(mapRowToEntity(rows[i]));
        }
    } catch (const std::exception& e) {
        std::cerr << "Error finding TripCities by city: " << e.what() << std::endl;
    }
    
    return result;
}

V<TripCity> TripCityRepository::findByTripAndCity(int tripId, int cityId) {
    V<TripCity> result;
    
    if (!db.isConnected()) {
        return result;
    }
    
    try {
        std::stringstream query;
        query << "SELECT id, trip_id, city_id, visit_order FROM trip_cities WHERE trip_id = " 
              << tripId << " AND city_id = " << cityId << " ORDER BY visit_order;";
        
        V<std::vector<std::string>> rows = db.executeSelect(query.str());
        
        for (size_t i = 0; i < rows.size(); i++) {
            result.push_back(mapRowToEntity(rows[i]));
        }
    } catch (const std::exception& e) {
        std::cerr << "Error finding TripCities by trip and city: " << e.what() << std::endl;
    }
    
    return result;
}

bool TripCityRepository::existsByTripAndOrder(int tripId, int visitOrder) {
    if (!db.isConnected()) {
        return false;
    }
    
    try {
        std::stringstream query;
        query << "SELECT COUNT(*) FROM trip_cities WHERE trip_id = " 
              << tripId << " AND visit_order = " << visitOrder << ";";
        
        V<std::vector<std::string>> result = db.executeSelect(query.str());
        
        if (result.size() > 0 && result[0].size() > 0) {
            int count = std::stoi(result[0][0]);
            return count > 0;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error checking if TripCity exists by trip and order: " << e.what() << std::endl;
    }
    
    return false;
}

bool TripCityRepository::saveAll(const V<TripCity>& tripCities) {
    if (!beginTransaction()) {
        return false;
    }
    
    try {
        for (size_t i = 0; i < tripCities.size(); i++) {
            TripCity tripCity = tripCities[i]; // Copy to allow modification
            if (!save(tripCity)) {
                rollbackTransaction();
                return false;
            }
        }
        return commitTransaction();
    } catch (const std::exception& e) {
        rollbackTransaction();
        std::cerr << "Error saving all TripCities: " << e.what() << std::endl;
        return false;
    }
}

bool TripCityRepository::removeByTrip(int tripId) {
    if (!db.isConnected()) {
        return false;
    }
    
    try {
        std::stringstream query;
        query << "DELETE FROM trip_cities WHERE trip_id = " << tripId << ";";
        return db.executeDelete(query.str());
    } catch (const std::exception& e) {
        std::cerr << "Error removing TripCities by trip: " << e.what() << std::endl;
    }
    
    return false;
}

bool TripCityRepository::reorderTripCities(int tripId, const V<TripCity>& newOrder) {
    if (!beginTransaction()) {
        return false;
    }
    
    try {
        // Remove existing cities for this trip
        if (!removeByTrip(tripId)) {
            rollbackTransaction();
            return false;
        }
        
        // Insert new order
        for (size_t i = 0; i < newOrder.size(); i++) {
            TripCity tripCity = newOrder[i];
            tripCity.setTripId(tripId);
            tripCity.setId(0); // Reset ID for new insert
            
            if (!save(tripCity)) {
                rollbackTransaction();
                return false;
            }
        }
        
        return commitTransaction();
    } catch (const std::exception& e) {
        rollbackTransaction();
        std::cerr << "Error reordering TripCities: " << e.what() << std::endl;
        return false;
    }
}

// Transaction support
bool TripCityRepository::beginTransaction() {
    return db.beginTransaction();
}

bool TripCityRepository::commitTransaction() {
    return db.commitTransaction();
}

bool TripCityRepository::rollbackTransaction() {
    return db.rollbackTransaction();
}

// Private helper methods
TripCity TripCityRepository::mapRowToEntity(const std::vector<std::string>& row) {
    if (row.size() < 4) {
        throw std::invalid_argument("Invalid row data for TripCity");
    }
    
    return TripCity(
        std::stoi(row[0]),  // id
        std::stoi(row[1]),  // trip_id
        std::stoi(row[2]),  // city_id
        std::stoi(row[3])   // visit_order
    );
}

std::string TripCityRepository::buildInsertQuery(const TripCity& tripCity) {
    std::stringstream query;
    query << "INSERT INTO trip_cities (trip_id, city_id, visit_order) VALUES ("
          << tripCity.getTripId() << ", " 
          << tripCity.getCityId() << ", " 
          << tripCity.getVisitOrder() << ") RETURNING id;";
    return query.str();
}

std::string TripCityRepository::buildUpdateQuery(const TripCity& tripCity) {
    std::stringstream query;
    query << "UPDATE trip_cities SET trip_id = " << tripCity.getTripId()
          << ", city_id = " << tripCity.getCityId()
          << ", visit_order = " << tripCity.getVisitOrder()
          << " WHERE id = " << tripCity.getId() << ";";
    return query.str();
}

std::string TripCityRepository::buildDeleteQuery(int id) {
    std::stringstream query;
    query << "DELETE FROM trip_cities WHERE id = " << id << ";";
    return query.str();
}

std::string TripCityRepository::buildSelectQuery(int id) {
    std::stringstream query;
    query << "SELECT id, trip_id, city_id, visit_order FROM trip_cities WHERE id = " << id << ";";
    return query.str();
}

std::string TripCityRepository::buildSelectAllQuery() {
    return "SELECT id, trip_id, city_id, visit_order FROM trip_cities ORDER BY trip_id, visit_order;";
}

std::string TripCityRepository::buildSelectByTripQuery(int tripId) {
    std::stringstream query;
    query << "SELECT id, trip_id, city_id, visit_order FROM trip_cities WHERE trip_id = " 
          << tripId << " ORDER BY visit_order;";
    return query.str();
}

std::string TripCityRepository::buildSelectByCityQuery(int cityId) {
    std::stringstream query;
    query << "SELECT id, trip_id, city_id, visit_order FROM trip_cities WHERE city_id = " 
          << cityId << " ORDER BY trip_id, visit_order;";
    return query.str();
}
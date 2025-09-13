/**
 * @file test_tripCity.cpp
 * @brief Test suite for TripCity functionality and database operations
 * @author CS1D Lab 3 Team
 * @date 2024
 * 
 * This file contains comprehensive tests for the TripCity functionality,
 * including database connectivity, data validation, and CRUD operations.
 * It serves as both a testing tool and a demonstration of the system's capabilities.
 */

#include "../include/header.hpp"
#include "../include/databaseManager.hpp"
#include "../include/entities/tripCities.hpp"
#include <iostream>
#include <vector>
#include <iomanip>

/**
 * @class TripCityTester
 * @brief Test class for TripCity functionality
 * 
 * This class provides comprehensive testing capabilities for the TripCity
 * system, including database connectivity tests, data validation, and
 * CRUD operation testing.
 */
class TripCityTester {
private:
    DatabaseManager& db; ///< Reference to database manager

public:
    /**
     * @brief Constructor for TripCityTester
     * 
     * Initializes the tester with a database connection.
     * Exits the application if database connection fails.
     */
    TripCityTester() : db(DatabaseManager::getInstance()) {
        if (!db.connect()) {
            std::cerr << "Failed to connect to database!" << std::endl;
            exit(1);
        }
    }

    /**
     * @brief Runs the complete test suite
     * 
     * Executes all test cases in sequence:
     * 1. Database connection test
     * 2. Cities data validation
     * 3. Trips data validation
     * 4. TripCity operations testing
     * 
     * Displays results in a formatted output with success/failure indicators.
     */
    void runAllTests() {
        std::cout << "\n" << std::string(60, '=') << std::endl;
        std::cout << "    TRIP CITY FUNCTIONS TEST SUITE" << std::endl;
        std::cout << std::string(60, '=') << std::endl;

        testDatabaseConnection();
        testCitiesData();
        testTripsData();
        testTripCityOperations();
        
        std::cout << "\n" << std::string(60, '=') << std::endl;
        std::cout << "    ALL TESTS COMPLETED" << std::endl;
        std::cout << std::string(60, '=') << std::endl;
    }

private:
    /**
     * @brief Tests database connectivity
     * 
     * Verifies that the database connection is established and functional.
     * This is a prerequisite for all other tests.
     */
    void testDatabaseConnection() {
        std::cout << "\n1. Testing Database Connection..." << std::endl;
        std::cout << std::string(40, '-') << std::endl;
        
        if (db.isConnected()) {
            std::cout << "✅ Database connection: SUCCESS" << std::endl;
        } else {
            std::cout << "❌ Database connection: FAILED" << std::endl;
        }
    }

    /**
     * @brief Tests cities data availability and displays sample data
     * 
     * Queries the cities table to verify data exists and displays
     * a sample of available cities for verification.
     */
    void testCitiesData() {
        std::cout << "\n2. Testing Cities Data..." << std::endl;
        std::cout << std::string(40, '-') << std::endl;
        
        std::string query = "SELECT COUNT(*) FROM cities;";
        auto result = db.executeSelect(query);
        
        if (!result.empty()) {
            int cityCount = std::stoi(result[0][0]);
            std::cout << "✅ Cities in database: " << cityCount << std::endl;
            
            if (cityCount > 0) {
                displayCities();
            } else {
                std::cout << "⚠️  No cities found in database!" << std::endl;
            }
        } else {
            std::cout << "❌ Failed to query cities" << std::endl;
        }
    }

    /**
     * @brief Displays a sample of cities from the database
     * 
     * Shows the first 10 cities in a formatted table for verification.
     * This helps ensure the data import was successful.
     */
    void displayCities() {
        std::string query = "SELECT id, name FROM cities ORDER BY name LIMIT 10;";
        auto result = db.executeSelect(query);
        
        if (!result.empty()) {
            std::cout << "\n🏙️ Sample Cities:" << std::endl;
            std::cout << std::setw(5) << "ID" << " | " << std::setw(30) << "City Name" << std::endl;
            std::cout << std::string(40, '-') << std::endl;
            
            for (const auto& row : result) {
                if (row.size() >= 2) {
                    std::string id = row[0];
                    std::string name = row[1];
                    std::cout << std::setw(5) << id << " | " << std::setw(30) << name << std::endl;
                }
            }
        }
    }

    /**
     * @brief Tests trips data availability and creates test data if needed
     * 
     * Verifies that trips exist in the database. If no trips are found,
     * creates a test trip for testing purposes.
     */
    void testTripsData() {
        std::cout << "\n3. Testing Trips Data..." << std::endl;
        std::cout << std::string(40, '-') << std::endl;
        
        std::string query = "SELECT COUNT(*) FROM trips;";
        auto result = db.executeSelect(query);
        
        if (!result.empty()) {
            int tripCount = std::stoi(result[0][0]);
            std::cout << "✅ Trips in database: " << tripCount << std::endl;
            
            if (tripCount == 0) {
                std::cout << "⚠️  No trips found. Creating test trip..." << std::endl;
                createTestTrip();
            } else {
                displayTrips();
            }
        } else {
            std::cout << "❌ Failed to query trips" << std::endl;
        }
    }

    /**
     * @brief Creates a test trip for testing purposes
     * 
     * Inserts a basic test trip into the database if no trips exist.
     * This ensures there's data available for testing TripCity operations.
     */
    void createTestTrip() {
        std::string query = "INSERT INTO trips (start_city_id, trip_type, total_distance) VALUES (NULL, 'test', 0.0);";
        if (db.executeQuery(query)) {
            std::cout << "✅ Test trip created successfully" << std::endl;
        } else {
            std::cout << "❌ Failed to create test trip" << std::endl;
        }
    }

    /**
     * @brief Displays sample trips from the database
     * 
     * Shows the first 5 trips in a formatted table for verification.
     */
    void displayTrips() {
        std::string query = "SELECT id, trip_type, total_distance FROM trips ORDER BY id LIMIT 5;";
        auto result = db.executeSelect(query);
        
        if (!result.empty()) {
            std::cout << "\n📋 Sample Trips:" << std::endl;
            std::cout << std::setw(5) << "ID" << " | " << std::setw(15) << "Type" << " | " << std::setw(10) << "Distance" << std::endl;
            std::cout << std::string(35, '-') << std::endl;
            
            for (const auto& row : result) {
                if (row.size() >= 3) {
                    std::string id = row[0];
                    std::string type = row[1];
                    std::string distance = row[2];
                    std::cout << std::setw(5) << id << " | " << std::setw(15) << type << " | " << std::setw(10) << distance << std::endl;
                }
            }
        }
    }

    /**
     * @brief Tests TripCity CRUD operations
     * 
     * Performs comprehensive testing of TripCity operations:
     * - Adding cities to trips
     * - Retrieving cities from trips
     * - Removing cities from trips
     * 
     * Uses the first available trip for testing.
     */
    void testTripCityOperations() {
        std::cout << "\n4. Testing TripCity Operations..." << std::endl;
        std::cout << std::string(40, '-') << std::endl;
        
        // Get first trip ID
        int tripId = getFirstTripId();
        if (tripId == -1) {
            std::cout << "❌ No trips available for testing" << std::endl;
            return;
        }
        
        std::cout << "Testing with Trip ID: " << tripId << std::endl;
        
        // Test adding cities to trip
        testAddCityToTrip(tripId);
        
        // Test getting cities for trip
        testGetCitiesForTrip(tripId);
        
        // Test removing city from trip
        testRemoveCityFromTrip(tripId);
    }

    /**
     * @brief Gets the first available trip ID for testing
     * @return int The first trip ID, or -1 if no trips exist
     */
    int getFirstTripId() {
        std::string query = "SELECT id FROM trips ORDER BY id LIMIT 1;";
        auto result = db.executeSelect(query);
        
        if (!result.empty() && !result[0].empty()) {
            return std::stoi(result[0][0]);
        }
        return -1;
    }

    /**
     * @brief Tests adding a city to a trip
     * @param tripId The ID of the trip to add a city to
     * 
     * Adds the first available city to the specified trip and verifies
     * the operation was successful.
     */
    void testAddCityToTrip(int tripId) {
        std::cout << "\n🔧 Testing Add City to Trip..." << std::endl;
        
        // Get first city ID
        std::string cityQuery = "SELECT id FROM cities ORDER BY id LIMIT 1;";
        auto cityResult = db.executeSelect(cityQuery);
        
        if (!cityResult.empty() && !cityResult[0].empty()) {
            int cityId = std::stoi(cityResult[0][0]);
            
            // Add city to trip
            std::string addQuery = "INSERT INTO trip_cities (trip_id, city_id, visit_order) VALUES (" + 
                                 std::to_string(tripId) + ", " + std::to_string(cityId) + ", 1);";
            
            if (db.executeQuery(addQuery)) {
                std::cout << "✅ Successfully added city " << cityId << " to trip " << tripId << std::endl;
            } else {
                std::cout << "❌ Failed to add city to trip" << std::endl;
            }
        } else {
            std::cout << "❌ No cities available for testing" << std::endl;
        }
    }

    /**
     * @brief Tests retrieving cities from a trip
     * @param tripId The ID of the trip to retrieve cities from
     * 
     * Queries and displays all cities associated with the specified trip,
     * including city names and visit orders.
     */
    void testGetCitiesForTrip(int tripId) {
        std::cout << "\n🔧 Testing Get Cities for Trip..." << std::endl;
        
        std::string query = "SELECT tc.id, tc.trip_id, tc.city_id, tc.visit_order, c.name " 
                           "FROM trip_cities tc "
                           "JOIN cities c ON tc.city_id = c.id "
                           "WHERE tc.trip_id = " + std::to_string(tripId) + " "
                           "ORDER BY tc.visit_order;";
        
        auto result = db.executeSelect(query);
        
        if (!result.empty()) {
            std::cout << "✅ Found " << result.size() << " cities in trip " << tripId << std::endl;
            
            std::cout << std::setw(5) << "ID" << " | " << std::setw(8) << "Trip ID" << " | " 
                      << std::setw(8) << "City ID" << " | " << std::setw(12) << "Visit Order" << " | " 
                      << std::setw(20) << "City Name" << std::endl;
            std::cout << std::string(70, '-') << std::endl;
            
            for (const auto& row : result) {
                if (row.size() >= 5) {
                    std::string id = row[0];
                    std::string tripId = row[1];
                    std::string cityId = row[2];
                    std::string visitOrder = row[3];
                    std::string cityName = row[4];
                    
                    std::cout << std::setw(5) << id << " | " << std::setw(8) << tripId << " | " 
                              << std::setw(8) << cityId << " | " << std::setw(12) << visitOrder << " | " 
                              << std::setw(20) << cityName << std::endl;
                }
            }
        } else {
            std::cout << "⚠️  No cities found in trip " << tripId << std::endl;
        }
    }

    /**
     * @brief Tests removing a city from a trip
     * @param tripId The ID of the trip to remove a city from
     * 
     * Removes the first city found in the specified trip and verifies
     * the operation was successful.
     */
    void testRemoveCityFromTrip(int tripId) {
        std::cout << "\n🔧 Testing Remove City from Trip..." << std::endl;
        
        // Get first city in trip
        std::string query = "SELECT city_id FROM trip_cities WHERE trip_id = " + std::to_string(tripId) + " LIMIT 1;";
        auto result = db.executeSelect(query);
        
        if (!result.empty() && !result[0].empty()) {
            int cityId = std::stoi(result[0][0]);
            
            // Remove city from trip
            std::string removeQuery = "DELETE FROM trip_cities WHERE trip_id = " + std::to_string(tripId) + 
                                    " AND city_id = " + std::to_string(cityId) + ";";
            
            if (db.executeQuery(removeQuery)) {
                std::cout << "✅ Successfully removed city " << cityId << " from trip " << tripId << std::endl;
            } else {
                std::cout << "❌ Failed to remove city from trip" << std::endl;
            }
        } else {
            std::cout << "⚠️  No cities in trip to remove" << std::endl;
        }
    }
};

/**
 * @brief Main function for running the test suite
 * @return int Exit status code (0 for success, 1 for failure)
 * 
 * Creates a TripCityTester instance and runs all tests.
 * Handles exceptions and provides appropriate error reporting.
 */
int main() {
    try {
        TripCityTester tester;
        tester.runAllTests();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}

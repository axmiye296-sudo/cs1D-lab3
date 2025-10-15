#include "../../include/repositories/CityRepository.hpp"
#include "../../include/databaseManager.hpp"              // Include the full DatabaseManager class

CityRepository::CityRepository(DatabaseManager& db) : database(db) {
    // The : database(db) part stores the database reference in our member variable
    // Now we can use 'database' to run SQL queries later
}

// Method to get all cities from the database
V<City> CityRepository::findAll() {
    V<City> result;  // Create empty V container to hold our City objects
                     // This will store all the cities we get from the database

    // SQL query to get all cities, ordered by name
    std::string query = "SELECT id, name FROM cities ORDER BY name;";
    // SELECT id, name = get the id and name columns
    // FROM cities = from the cities table
    // ORDER BY name = sort by name alphabetically

    // Execute the query - this returns database rows as strings
    auto dbResult = database.executeSelect(query);
    // database.executeSelect() runs our SQL query
    // It returns V<std::vector<std::string>> - a container of rows, each row is a vector of strings
    // auto means the compiler figures out the type for us

    // Loop through each row from the database
    for (const auto& row : dbResult) {
        // const auto& row = for each row in dbResult, call it 'row'
        // const means we won't change the row
        // auto means the compiler figures out the type
        // & means we're using a reference (not copying the data)

        // Convert the database row to a City object
        City city = mapRowToEntity(row);
        // mapRowToEntity() takes a row (vector of strings) and converts it to a City object

        // Add the City to our result container
        result.push_back(city);
        // push_back() adds the city to the end of our V container
    }

    return result;
}

// Helper method - converts a database row to a City object
City CityRepository::mapRowToEntity(const std::vector<std::string>& row) {
    City city;  // Create empty City object
                // This will hold the data from the database row

    // Convert string data to proper types
    city.setId(std::stoi(row[0]));      // Convert "1" (string) to 1 (int)
                                        // std::stoi = string to integer
                                        // row[0] = first column (id)
                                        // setId() stores the ID in our City object

    city.setName(row[1]);               // "Paris" (string) stays "Paris" (string)
                                        // row[1] = second column (name)
                                        // setName() stores the name in our City object

    return city;
}

// Insert new city into database
bool CityRepository::insert(const City& city) {
    try {
        // Insert with explicit ID so we can reuse deleted IDs deterministically
        std::string query = "INSERT INTO cities (id, name) VALUES (" +
                           std::to_string(city.getId()) + ", '" + city.getName() + "');";
        return database.executeUpdate(query);
    } catch (const std::exception& e) {
        std::cerr << "Error inserting city: " << e.what() << std::endl;
        return false;
    }
}

// Update existing city in database
bool CityRepository::update(const City& city) {
    try {
        std::string query = "UPDATE cities SET name = '" + city.getName() + 
                           "' WHERE id = " + std::to_string(city.getId()) + ";";
        return database.executeUpdate(query);
    } catch (const std::exception& e) {
        std::cerr << "Error updating city: " << e.what() << std::endl;
        return false;
    }
}

// Delete city from database
bool CityRepository::deleteById(int cityId) {
    try {
        std::string query = "DELETE FROM cities WHERE id = " + std::to_string(cityId) + ";";
        return database.executeUpdate(query);
    } catch (const std::exception& e) {
        std::cerr << "Error deleting city: " << e.what() << std::endl;
        return false;
    }
}

// Find specific city by ID
City* CityRepository::findById(int cityId) {
    try {
        std::string query = "SELECT id, name FROM cities WHERE id = " + std::to_string(cityId) + ";";
        auto dbResult = database.executeSelect(query);
        
        if (!dbResult.empty()) {
            City* city = new City();
            *city = mapRowToEntity(dbResult[0]);
            return city;
        }
        return nullptr;
    } catch (const std::exception& e) {
        std::cerr << "Error finding city: " << e.what() << std::endl;
        return nullptr;
    }
}
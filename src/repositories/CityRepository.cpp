#include "../../include/repositories/cityRepository.hpp"
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
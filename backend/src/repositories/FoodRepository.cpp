#include "../../include/repositories/FoodRepository.hpp"
#include "../../include/databaseManager.hpp"


// Constructor - store the database connection for later use
FoodRepository::FoodRepository(DatabaseManager& db) : database(db) {
    // The : database(db) part stores the database reference in our member variable
    // Now we can use 'database' to run SQL queries later
}

// Method to get all foods from the database
V<Food> FoodRepository::findAll() {
    V<Food> result;  // Create empty V container to hold our Food objects
                     // This will store all the foods we get from the database

    // SQL query to get all foods, ordered by name
    std::string query = "SELECT id, name, city_id, price FROM foods ORDER BY name;";
    // SELECT id, name, city_id, price = get these 4 columns
    // FROM foods = from the foods table
    // ORDER BY name = sort by name alphabetically

    // Execute the query
    auto dbResult = database.executeSelect(query);
    // database.executeSelect() runs our SQL query
    // It returns V<std::vector<std::string>> - a container of rows, each row is a vector of strings

    // Process the results - loop through each row from the database
    for (const auto& row : dbResult) {
        // const auto& row = for each row in dbResult, call it 'row'
        // const means we won't change the row
        // auto means the compiler figures out the type
        // & means we're using a reference (not copying the data)

        Food food = mapRowToEntity(row);  // Convert the database row to a Food object
        result.push_back(food);           // Add the Food to our result container
    }

    return result;  // Return all the Food objects we found
}

// Method to get foods for a specific city
V<Food> FoodRepository::findByCityId(int cityId) {
    V<Food> result;  // Create empty V container to hold our Food objects
                     // This will store all the foods for the specified city

    // SQL query with WHERE clause to filter by city_id
    std::string query = "SELECT id, name, city_id, price FROM foods WHERE city_id = " + std::to_string(cityId) + " ORDER BY name;";
    // SELECT id, name, city_id, price = get these 4 columns
    // FROM foods = from the foods table
    // WHERE city_id = " + std::to_string(cityId) = only get foods where city_id matches our parameter
    // std::to_string() converts the integer cityId to a string for the SQL query
    // ORDER BY name = sort by name alphabetically

    // Execute the query
    auto dbResult = database.executeSelect(query);
    // database.executeSelect() runs our SQL query
    // It returns V<std::vector<std::string>> - a container of rows, each row is a vector of strings

    // Process the results - loop through each row from the database
    for (const auto& row : dbResult) {
        // const auto& row = for each row in dbResult, call it 'row'
        // const means we won't change the row
        // auto means the compiler figures out the type
        // & means we're using a reference (not copying the data)

        Food food = mapRowToEntity(row);  // Convert the database row to a Food object
        result.push_back(food);           // Add the Food to our result container
    }

    return result;  // Return all the Food objects we found for this city
}

// Helper method - converts a database row to a Food object
Food FoodRepository::mapRowToEntity(const std::vector<std::string>& row) {
    Food food;  // Create empty Food object
                // This will hold the data from the database row

    // Convert string data to proper types
    food.setId(std::stoi(row[0]));      // Convert "1" (string) to 1 (int)
                                        // std::stoi = string to integer
                                        // row[0] = first column (id)
                                        // setId() stores the ID in our Food object

    food.setName(row[1]);               // "Croissant" (string) stays "Croissant" (string)
                                        // row[1] = second column (name)
                                        // setName() stores the name in our Food object

    food.setCityId(std::stoi(row[2]));  // Convert "1" (string) to 1 (int)
                                        // std::stoi = string to integer
                                        // row[2] = third column (city_id)
                                        // setCityId() stores the city ID in our Food object

    food.setPrice(std::stod(row[3]));   // Convert "2.50" (string) to 2.50 (double)
                                        // std::stod = string to double
                                        // row[3] = fourth column (price)
                                        // setPrice() stores the price in our Food object

    return food;  // Return the populated Food object
}
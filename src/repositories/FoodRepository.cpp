#include "../../include/repositories/FoodRepository.hpp"
#include "../../include/databaseManager.hpp"

// Constructor – store the database connection for later use
FoodRepository::FoodRepository(DatabaseManager& db) : database(db) {
    // The : database(db) part stores the database reference in our member variable
    // Now we can use 'database' to run SQL queries later
}

// Method to get all foods from the database
std::vector<Food> FoodRepository::findAll() {
    std::vector<Food> result; 
    // Create empty vector to hold our Food objects
    // This will store all the foods we get from the database

    // SQL query to get all foods, ordered by name
    std::string query = "SELECT id, name, city_id, price FROM foods ORDER BY name;";
    // SELECT id, name, city_id, price = get these 4 columns
    // FROM foods = from the foods table
    // ORDER BY name = sort by name alphabetically

    // Execute the query
    auto dbResult = database.executeSelect(query);
    // database.executeSelect(query) runs our SQL query
    // It returns std::vector<std::vector<std::string>> -> a container of rows, each row is a vector of strings

    // Process the results – loop through each row from the database
    for (const auto& row : dbResult) {
        // const auto& row = for each row in dbResult, call it 'row'
        // const means we won't change the row

        // Here you would typically construct a Food object from the row data
        // Example (assuming row = {id, name, city_id, price}):
        int id = std::stoi(row[0]);
        std::string name = row[1];
        int cityId = std::stoi(row[2]);
        double price = std::stod(row[3]);

        result.emplace_back(id, name, cityId, price);
    }

    return result;
}

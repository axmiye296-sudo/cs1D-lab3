/**
 * @file FoodRepository.cpp
 * @brief Implementation of FoodRepository class
 */

#include "../../include/repositories/FoodRepository.hpp"
#include "../../include/databaseManager.hpp"

// ============================================================================
// CONSTRUCTOR
// ============================================================================

/**
 * @brief Constructor implementation
 * @param db Reference to DatabaseManager instance
 * 
 * Initializes the repository with a database connection.
 * The database reference is stored for later use in SQL operations.
 */
FoodRepository::FoodRepository(DatabaseManager& db) : database(db) {
    // The : database(db) part stores the database reference in our member variable
    // Now we can use 'database' to run SQL queries later
}

// ============================================================================
// PUBLIC METHODS
// ============================================================================

/**
 * @brief Retrieve all foods from the database
 * @return Vector containing all Food objects from the database
 * 
 * Executes a SELECT query to fetch all foods and converts
 * the results into Food objects. Results are ordered alphabetically by name.
 */
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

/**
 * @brief Find foods by city ID
 * @param cityId The ID of the city to search for
 * @return Vector containing Food objects for the specified city
 * 
 * Retrieves all foods associated with a specific city.
 * Results are ordered alphabetically by name.
 */
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

// ============================================================================
// ADMIN METHODS
// ============================================================================

/**
 * @brief Insert a new food into the database
 * @param food The Food object to insert
 * @return True if insertion successful, false otherwise
 * 
 * Adds a new food record to the database. The food ID should
 * be set before calling this method.
 */
bool FoodRepository::insert(const Food& food) {
    try {
        // Insert with explicit ID so we can reuse deleted IDs deterministically
        std::string query = "INSERT INTO foods (id, name, city_id, price) VALUES (" +
                           std::to_string(food.getId()) + ", '" + 
                           food.getName() + "', " + 
                           std::to_string(food.getCityId()) + ", " + 
                           std::to_string(food.getPrice()) + ");";
        return database.executeUpdate(query);
    } catch (const std::exception& e) {
        std::cerr << "Error inserting food: " << e.what() << std::endl;
        return false;
    }
}

/**
 * @brief Update an existing food in the database
 * @param food The Food object with updated information
 * @return True if update successful, false otherwise
 * 
 * Modifies an existing food record based on the food's ID.
 */
bool FoodRepository::update(const Food& food) {
    try {
        std::string query = "UPDATE foods SET name = '" + food.getName() + 
                           "', city_id = " + std::to_string(food.getCityId()) + 
                           ", price = " + std::to_string(food.getPrice()) + 
                           " WHERE id = " + std::to_string(food.getId()) + ";";
        return database.executeUpdate(query);
    } catch (const std::exception& e) {
        std::cerr << "Error updating food: " << e.what() << std::endl;
        return false;
    }
}

/**
 * @brief Delete a food from the database by ID
 * @param foodId The ID of the food to delete
 * @return True if deletion successful, false otherwise
 * 
 * Removes a food record from the database using its unique ID.
 */
bool FoodRepository::deleteById(int foodId) {
    try {
        std::string query = "DELETE FROM foods WHERE id = " + std::to_string(foodId) + ";";
        return database.executeUpdate(query);
    } catch (const std::exception& e) {
        std::cerr << "Error deleting food: " << e.what() << std::endl;
        return false;
    }
}

/**
 * @brief Find a specific food by its ID
 * @param foodId The ID of the food to find
 * @return Pointer to Food object if found, nullptr otherwise
 * 
 * Searches for a food with the specified ID and returns
 * a pointer to the Food object if found. Caller is responsible
 * for deleting the returned pointer.
 */
Food* FoodRepository::findById(int foodId) {
    try {
        std::string query = "SELECT id, name, city_id, price FROM foods WHERE id = " + std::to_string(foodId) + ";";
        auto dbResult = database.executeSelect(query);
        
        if (!dbResult.empty()) {
            Food* food = new Food();
            *food = mapRowToEntity(dbResult[0]);
            return food;
        }
        return nullptr;
    } catch (const std::exception& e) {
        std::cerr << "Error finding food: " << e.what() << std::endl;
        return nullptr;
    }
}

// ============================================================================
// PRIVATE HELPER METHODS
// ============================================================================

/**
 * @brief Convert database row to Food object
 * @param row Vector of strings representing a database row
 * @return Food object created from the row data
 * 
 * Maps a database row (vector of strings) to a Food object.
 * This is a helper method used internally by other repository methods.
 */
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
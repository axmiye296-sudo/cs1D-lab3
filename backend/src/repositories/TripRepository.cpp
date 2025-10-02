#include "../../include/repositories/TripRepository.hpp"
#include "../../include/databaseManager.hpp"

TripRepository::TripRepository(DatabaseManager& db) : database(db) {
    // The : database(db) part stores the database reference in our member variable
    // Now we can use 'database' to run SQL queries later
}

// This function will return a vector of trip objects
// that match the trip type (starting city)
V<Trip> TripRepository::findByType(const std::string& tripType) {
    //Creating a trip container/vector to hold trip objects
    V<Trip> result;

    // SQL query to get all trips by type
    std::string query = "SELECT id, start_city_id, trip_type, total_distance "
                        "FROM trips "
                        "WHERE trip_type = '" + tripType + "' "
                        "ORDER BY id;";
    // Execute the query
    auto dbResult = database.executeSelect(query);

    // Convert results to Trip objects
    for (const auto& row : dbResult) {
        if (row.size() >= 4) {  // Ensure we have all required columns
            Trip trip = mapRowToEntity(row);
            result.push_back(trip);
        }
    }

    return result;
}

// This function is for custom start city
V<Trip> TripRepository::findByStartCity(int startCityId) {
    V<Trip> result;

     // Validate input
    if (startCityId <= 0) {
        return result;  // Return empty vector for invalid city ID
    }

    // Create the SQL query
    std::string query = "SELECT id, start_city_id, trip_type, total_distance "
                        "FROM trips "
                        "WHERE start_city_id = " + std::to_string(startCityId) + " "
                        "ORDER BY id;";

    // Execute the query
    auto dbResult = database.executeSelect(query);

    // Convert results to Trip objects
    for (const auto& row : dbResult) {
        if (row.size() >= 4) {
            Trip trip = mapRowToEntity(row);
            result.push_back(trip);
        }
    }

    return result;
}

// Expected row format from database:
// row[0] = "5"           // id as string
// row[1] = "1"           // start_city_id as string
// row[2] = "paris_tour"  // trip_type as string
// row[3] = "2847.5"      // total_distance as string

// Converts to:
// Trip(5, 1, "paris_tour", 2847.5)
Trip TripRepository::mapRowToEntity(const std::vector<std::string>& row) {
    try {
        // Convert string values to appropriate types
        int id = std::stoi(row[0]);                    // id column
        int startCityId = std::stoi(row[1]);          // start_city_id column
        std::string tripType = row[2];                 // trip_type column
        double totalDistance = std::stod(row[3]);      // total_distance column

        // Create and return Trip object
        return Trip(id, startCityId, tripType, totalDistance);

    } catch (const std::exception& e) {
        std::cerr << "Error converting database row to Trip: " << e.what() << std::endl;
        // Return default Trip object on conversion error
        return Trip();
    }
}

    // This function will create a new trip record in the
    // trip table
std::string TripRepository::buildInsertQuery(const Trip& trip) {
    // Build INSERT query - don't include ID since it's auto-increment
    std::string query = "INSERT INTO trips (start_city_id, trip_type, total_distance) VALUES (";
    // Add start_city_id
    query += std::to_string(trip.getStartCityId()) + ", ";

    // Add trip_type (with quotes since it's a string)
    query += "'" + trip.getTripType() + "', ";

    // Add total_distance
    query += std::to_string(trip.getTotalDistance());

    // Close the VALUES clause
    query += ");";

    return query;
}


    std::string TripRepository::buildUpdateQuery(const Trip& trip) {
        // Build UPDATE SQL query
        std::string query = "UPDATE trips SET ";

        // Set each field that can be updated
        query += "start_city_id = " + std::to_string(trip.getStartCityId()) + ", ";
        query += "trip_type = '" + trip.getTripType() + "', ";
        query += "total_distance = " + std::to_string(trip.getTotalDistance());

        // Add WHERE clause to specify which record to update
        query += " WHERE id = " + std::to_string(trip.getId()) + ";";

        return query;
    }

bool TripRepository::save(Trip& trip) {
    try {
        std::string query;

        if (trip.getId() == 0) {
            // New trip - use INSERT
            query = buildInsertQuery(trip);

            if (database.executeQuery(query)) {
                // ✅ PROPER FIX: Get the actual auto-generated ID from database
                std::string getIdQuery = "SELECT last_insert_rowid()";
                auto result = database.executeSelect(getIdQuery);

                if (!result.empty() && !result[0].empty()) {
                    int newId = std::stoi(result[0][0]);
                    trip.setId(newId);
                    std::cout << "✅ Trip saved with database ID: " << newId << std::endl;
                } else {
                    // Fallback to incremental ID if database query fails
                    static int dummyId = 1;
                    trip.setId(dummyId++);
                    std::cout << "⚠️ Using fallback ID: " << trip.getId() << std::endl;
                }

                return true;
            }
        } else {
            // Existing trip - use UPDATE
            query = buildUpdateQuery(trip);
            return database.executeQuery(query);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error saving trip: " << e.what() << std::endl;
        return false;
    }
}


bool TripRepository::load(int id, Trip& trip) {
    if (id <= 0) {
        std::cerr << "Invalid trip ID: " << id << std::endl;
        return false;
    }

    try {
        // Build SELECT query for specific ID
        std::string query = "SELECT id, start_city_id, trip_type, total_distance "
                           "FROM trips "
                           "WHERE id = " + std::to_string(id) + ";";

        // Execute the query
        auto dbResult = database.executeSelect(query);

        // Check if we found the trip
        if (dbResult.empty()) {
            std::cerr << "Trip with ID " << id << " not found" << std::endl;
            return false;
        }

        // Get the first (and should be only) result
        const auto& row = dbResult[0];

        if (row.size() < 4) {
            std::cerr << "Invalid database row for trip ID " << id << std::endl;
            return false;
        }

        // Convert database row to Trip object
        trip = mapRowToEntity(row);

        return true;

    } catch (const std::exception& e) {
        std::cerr << "Error loading trip with ID " << id << ": " << e.what() << std::endl;
        return false;
    }
}

V<Trip> TripRepository::findAll() {
    V<Trip> result;
    
    std::string query = "SELECT id, start_city_id, trip_type, total_distance FROM trips ORDER BY id;";
    
    auto dbResult = database.executeSelect(query);
    
    for (const auto& row : dbResult) {
        if (row.size() >= 4) {
            result.push_back(mapRowToEntity(row));
        }
    }
    
    return result;
}



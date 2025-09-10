/**
 * JSON Mock Database Test Application
 * Demonstrates how to use the JSON mock database system
 * No PostgreSQL required - perfect for development and testing
 */

#include "../include/header.hpp"
#include "../include/entities/tripCities.hpp"
#include "../include/jsonDatabase.hpp"
#include "../include/tripCityDataAccess.hpp"
#include "../include/tripCityService.hpp"

int main() {
    std::cout << "=== JSON Mock Database Test ===" << std::endl;
    
    // Initialize JSON database
    JsonDatabase db("./mock_data");
    
    // Initialize data access layer
    TripCityDataAccess dataAccess(db);
    
    // Initialize service layer
    TripCityService service(dataAccess);
    
    // Test operations
    std::cout << "\n1. Adding cities to trip 1..." << std::endl;
    service.addCityToTrip(1, 1, 1);  // New York
    service.addCityToTrip(1, 2, 2);  // Los Angeles
    service.addCityToTrip(1, 3, 3);  // Chicago
    
    std::cout << "\n2. Adding cities to trip 2..." << std::endl;
    service.addCityToTrip(2, 2, 1);  // Los Angeles
    service.addCityToTrip(2, 3, 2);  // Chicago
    
    std::cout << "\n3. Getting cities for trip 1..." << std::endl;
    V<TripCity> cities1 = service.getCitiesForTrip(1);
    std::cout << "Found " << cities1.size() << " cities in trip 1" << std::endl;
    
    std::cout << "\n4. Getting cities for trip 2..." << std::endl;
    V<TripCity> cities2 = service.getCitiesForTrip(2);
    std::cout << "Found " << cities2.size() << " cities in trip 2" << std::endl;
    
    std::cout << "\n5. Printing all trip cities..." << std::endl;
    service.printTripCities(1);
    service.printTripCities(2);
    
    std::cout << "\n6. Removing city 2 from trip 1..." << std::endl;
    if (service.removeCityFromTrip(1, 2)) {
        std::cout << "City 2 removed from trip 1" << std::endl;
    }
    
    std::cout << "\n7. Final state of trip 1..." << std::endl;
    service.printTripCities(1);
    
    std::cout << "\n8. All trip_cities data..." << std::endl;
    dataAccess.printAllTripCities();
    
    return 0;
}

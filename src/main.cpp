#include "../include/header.hpp"
#include "../include/entities/tripCities.hpp"
#include "../include/databaseManager.hpp"
#include "../include/repositories/TripCityRepository.hpp"
#include "../include/services/TripCityService.hpp"

int main() {
    // Initialize database
    DatabaseManager& db = DatabaseManager::getInstance();
    db.connect();

    // Initialize repository
    auto repository = std::make_unique<TripCityRepository>(db);

    // Initialize service
    auto service = std::make_unique<TripCityService>(std::move(repository));

    // Use service instead of direct entity
    if (service->addCityToTrip(1, 5, 2)) {
        std::cout << "City added to trip successfully" << std::endl;
    }

    V<TripCity> cities = service->getCitiesForTrip(1);
    std::cout << "Found " << cities.size() << " cities in trip 1" << std::endl;
    
    return 0;
}
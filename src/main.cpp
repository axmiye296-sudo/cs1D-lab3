#include "../include/header.hpp"
#include <iostream>
#include <iomanip>
#include "../include/databaseManager.hpp"
#include "../include/repositories/TripRepository.hpp"
#include "../include/repositories/CityDistanceRepository.hpp"
#include "../include/repositories/CityRepository.hpp"
#include "../include/services/TripService.hpp"
#include "../include/entities/Trip.hpp"
#include "../include/entities/TripCity.hpp"

int main() {
    // 1) Boot DB
    auto& db = DatabaseManager::getInstance();
    if (!db.connect()) {
        std::cerr << "❌ DB connect failed\n";
        return 1;
    }

    // 2) Wire up repositories & services
    TripRepository        tripRepo(db);
    CityDistanceRepository distRepo(db);
    CityRepository        cityRepo(db);       // <-- only ONE CityRepository
    TripService           tripSvc(tripRepo, distRepo);

    // 2.5) Let user pick a start city
    std::cout << "\n\033[1mAvailable Cities\033[0m\n";
    std::cout << std::string(40, '-') << "\n";
    auto cityRows = db.executeSelect("SELECT id, name FROM cities ORDER BY id;");
    for (const auto& row : cityRows) {
        if (row.size() >= 2) {
            std::cout << "  "
                      << std::setw(3) << row[0] << "  |  " << row[1] << "\n";
        }
    }
    std::cout << std::string(40, '-') << "\n";

    int startCityId = 0;
    std::cout << "👉 Enter the starting city ID: ";
    if (!(std::cin >> startCityId)) {
        std::cerr << "❌ Invalid input.\n";
        return 1;
    }

    // 3) Create a new trip
    Trip trip;
    trip.setStartCityId(startCityId);   // <-- use the user's choice
    trip.setTripType("custom");
    trip.setTotalDistance(0);

    if (!tripRepo.save(trip)) {
        std::cerr << "❌ Could not save trip to DB\n";
        return 1;
    }
    std::cout << "✅ Trip created with ID: " << trip.getId() << "\n";

    // 4) Build shortest trip
    tripSvc.CreateShortestTrip(trip, trip.getStartCityId());

    // 5) Pretty summary
    std::cout << "\n\033[1m--- Trip Summary ---\033[0m\n";
    std::cout << "Trip ID: " << trip.getId() << "\n";
    std::cout << "Start City: " << cityRepo.getCityNameById(trip.getStartCityId())
              << " (id=" << trip.getStartCityId() << ")\n\n";

    std::cout << std::left
              << std::setw(6)  << "Order"
              << std::setw(10) << "City ID"
              << "City Name\n";
    std::cout << std::string(40, '-') << "\n";

    int order = 1;
    for (const auto& tc : trip.getTripList()) {
        std::string cityName = cityRepo.getCityNameById(tc.getCityId());
        std::cout << std::left
                  << std::setw(6)  << order++
                  << std::setw(10) << tc.getCityId()
                  << (cityName.empty() ? "[Unknown City]" : cityName)
                  << "  (visit order " << tc.getVisitOrder() << ")\n";
    }

    std::cout << std::string(40, '-') << "\n";
    std::cout << "Total distance: \033[1m" << trip.getTotalDistance() << " km\033[0m\n";

    return 0;
}
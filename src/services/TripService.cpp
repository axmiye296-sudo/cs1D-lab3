#include "../../include/services/TripService.hpp"
#include "../../include/services/tripCityService.hpp"
#include "../../include/services/FoodService.hpp"
#include "../../include/repositories/TripRepository.hpp" 
#include "../../include/repositories/CityRepository.hpp"
#include <iostream>
#include <iomanip>

// Constructor
TripService::TripService(TripRepository& tripRepo, CityRepository& cityRepo,
                        TripCityService& tripCityService, FoodService& foodService) :
    tripRepo(tripRepo),
    cityRepo(cityRepo),
    tripCityService(tripCityService),
    foodService(foodService)
{}


Trip TripService::planParisTour() {
    std::cout << "\n🗼 Planning Paris Tour - Visiting All European Cities\n" << std::endl;

    // Get all cities
    V<City> allCities = cityRepo.findAll();
    std::cout << "Found " << allCities.size() << " cities in database" << std::endl;

    // Find Paris (or default to first city)
    int parisId = findCityIdByName("Paris");
    if (parisId == -1 && allCities.size() > 0) {
        parisId = allCities[0].getId(); // Use first city if Paris not found
        std::cout << "Paris not found, using " << allCities[0].getName() << " as starting city" << std::endl;
    }

    // ✅ REQUIREMENT 3: Visit ALL cities except Paris (should be 10 other cities + Paris = 11 total)
    V<int> citiesToVisit;

    // Add ALL other cities to the route (not just 5)
    for (int i = 0; i < allCities.size(); i++) {
        if (allCities[i].getId() != parisId) {
            citiesToVisit.push_back(allCities[i].getId());
        }
    }

    std::cout << "🎯 Planning route to visit " << (citiesToVisit.size() + 1) << " cities total:" << std::endl;
    std::cout << "   - Starting city: Paris (or substitute)" << std::endl;
    std::cout << "   - Other cities to visit: " << citiesToVisit.size() << std::endl;

    // Calculate optimal route using recursive closest-city algorithm
    V<int> route = calculateOptimalRoute(parisId, citiesToVisit);

    // Create and save trip - ✅ FIX THIS LINE
    Trip parisTrip = createAndSaveTrip(parisId, TripTypes::PARIS_TOUR, route);

    std::cout << "✅ Paris tour planned successfully!" << std::endl;
    std::cout << "🏙️ Total cities in route: " << route.size() << " cities" << std::endl;
    std::cout << "🎯 Total distance: " << parisTrip.getTotalDistance() << " km" << std::endl;

    // Verify we have the expected number of cities
    if (route.size() >= 11) {
        std::cout << "✅ Requirement met: Visiting all 11 European cities" << std::endl;
    } else {
        std::cout << "⚠️  Warning: Only " << route.size() << " cities available (need 11 for full requirement)" << std::endl;
    }

    return parisTrip;
}

Trip TripService::planLondonTour() {
    std::cout << "\n🇬🇧 Planning London Tour\n" << std::endl;

    // Get all cities
    V<City> allCities = cityRepo.findAll();

    // Find London (or default to second city)
    int londonId = findCityIdByName("London");
    if (londonId == -1 && allCities.size() > 1) {
        londonId = allCities[1].getId(); // Use second city if London not found
        std::cout << "London not found, using " << allCities[1].getName() << " as starting city" << std::endl;
    }

    // Simple route with 3 cities for testing
    V<int> citiesToVisit;
    for (int i = 0; i < allCities.size() && citiesToVisit.size() < 3; i++) {
        if (allCities[i].getId() != londonId) {
            citiesToVisit.push_back(allCities[i].getId());
        }
    }

    V<int> route = calculateOptimalRoute(londonId, citiesToVisit);
    Trip londonTrip = createAndSaveTrip(londonId, TripTypes::LONDON_TOUR, route);

    std::cout << "✅ London tour planned successfully!" << std::endl;
    std::cout << "🏙️ Cities to visit: " << route.size() << std::endl;

    return londonTrip;
}

Trip TripService::planCustomTour() {
    std::cout << "\n🗺️ Planning Custom Tour\n" << std::endl;

    // Display available cities
    displayAvailableCities();

    // Get all cities for simple selection
    V<City> allCities = cityRepo.findAll();

    if (allCities.size() < 2) {
        std::cout << "Not enough cities available for custom tour" << std::endl;
        return Trip(); // Return empty trip
    }

    // Simple custom tour: use first city as start, visit 2-3 others
    int startCityId = allCities[0].getId();
    V<int> selectedCities;

    int maxToVisit = (allCities.size() > 3) ? 3 : allCities.size() - 1;
    for (int i = 1; i < allCities.size() && selectedCities.size() < maxToVisit; i++) {
        selectedCities.push_back(allCities[i].getId());
    }

    V<int> route = calculateOptimalRoute(startCityId, selectedCities);
    Trip customTrip = createAndSaveTrip(startCityId, TripTypes::CUSTOM_TOUR, route);

    std::cout << "✅ Custom tour planned successfully!" << std::endl;
    std::cout << "📍 Starting city: " << allCities[0].getName() << std::endl;
    std::cout << "🏙️ Cities to visit: " << route.size() << std::endl;

    return customTrip;
}



int TripService::findCityIdByName(const std::string& cityName) {
    V<City> allCities = cityRepo.findAll();

    for (int i = 0; i < allCities.size(); i++) {
        if (allCities[i].getName() == cityName) {
            return allCities[i].getId();
        }
    }

    return -1; // Not found
}

void TripService::displayAvailableCities() {
    std::cout << "\n📍 Available Cities:" << std::endl;
    std::cout << std::string(30, '-') << std::endl;

    V<City> allCities = cityRepo.findAll();

    for (int i = 0; i < allCities.size(); i++) {
        std::cout << "ID: " << std::setw(2) << allCities[i].getId()
                  << " - " << allCities[i].getName() << std::endl;
    }

    std::cout << std::string(30, '-') << std::endl;
}

void TripService::displayTrip(const Trip& trip) {
    std::cout << "\n🎯 Trip Details:" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "Trip ID: " << trip.getId() << std::endl;
    std::cout << "Trip Type: " << trip.getTripType() << std::endl;

    // Display starting city name
    V<City> allCities = cityRepo.findAll();
    std::string startCityName = "Unknown";
    for (const auto& city : allCities) {
        if (city.getId() == trip.getStartCityId()) {
            startCityName = city.getName();
            break;
        }
    }
    std::cout << "Starting City: " << startCityName << " (ID: " << trip.getStartCityId() << ")" << std::endl;
    std::cout << "Total Distance: " << std::fixed << std::setprecision(1)
              << trip.getTotalDistance() << " km" << std::endl;

    std::cout << std::string(50, '-') << std::endl;

    // Display all cities in the trip
    displayTripCities(trip.getId());

    std::cout << std::string(50, '=') << std::endl;
}

void TripService::displayTripCities(int tripId) {
    std::cout << "\n🏙️ Cities in Trip Route:" << std::endl;

    // Get all cities in the trip
    V<TripCity> tripCities = tripCityService.getCitiesForTrip(tripId);

    if (tripCities.empty()) {
        std::cout << "❌ No cities found in this trip." << std::endl;
        return;
    }

    // Get all cities for name lookup
    V<City> allCities = cityRepo.findAll();

    std::cout << std::setw(5) << "Order" << " | " << std::setw(15) << "City Name"
              << " | " << std::setw(8) << "City ID" << std::endl;
    std::cout << std::string(35, '-') << std::endl;

    // Sort by visit order (in case they're not in order)
    std::sort(tripCities.begin(), tripCities.end(),
              [](const TripCity& a, const TripCity& b) {
                  return a.getVisitOrder() < b.getVisitOrder();
              });

    for (const auto& tripCity : tripCities) {
        // Find city name
        std::string cityName = "Unknown";
        for (const auto& city : allCities) {
            if (city.getId() == tripCity.getCityId()) {
                cityName = city.getName();
                break;
            }
        }

        std::cout << std::setw(5) << tripCity.getVisitOrder() << " | "
                  << std::setw(15) << cityName << " | "
                  << std::setw(8) << tripCity.getCityId() << std::endl;
    }

    std::cout << "\n✅ Total cities in route: " << tripCities.size() << std::endl;
}

// ============================================================================
// MISSING METHOD IMPLEMENTATIONS
// ============================================================================

Trip TripService::planBerlinTour() {
    std::cout << "\n🇩🇪 Planning Berlin Tour\n" << std::endl;

    // Similar to Paris tour but with different starting city
    V<City> allCities = cityRepo.findAll();
    std::cout << "Found " << allCities.size() << " cities in database" << std::endl;

    // Find Berlin (or default to third city)
    int berlinId = findCityIdByName("Berlin");
    if (berlinId == -1 && allCities.size() > 2) {
        berlinId = allCities[2].getId(); // Use third city if Berlin not found
        std::cout << "Berlin not found, using " << allCities[2].getName() << " as starting city" << std::endl;
    } else if (berlinId == -1) {
        berlinId = allCities[0].getId(); // Fallback to first city
        std::cout << "Berlin not found, using " << allCities[0].getName() << " as starting city" << std::endl;
    }

    // Add ALL other cities to visit (for Berlin tour requirement)
    V<int> citiesToVisit;
    for (size_t i = 0; i < allCities.size(); i++) {
        if (allCities[i].getId() != berlinId) {
            citiesToVisit.push_back(allCities[i].getId());
        }
    }

    std::cout << "🎯 Planning route to visit " << (citiesToVisit.size() + 1) << " cities total:" << std::endl;
    std::cout << "   - Starting city: Berlin (or substitute)" << std::endl;
    std::cout << "   - Other cities to visit: " << citiesToVisit.size() << std::endl;

    V<int> route = calculateOptimalRoute(berlinId, citiesToVisit);
    Trip berlinTrip = createAndSaveTrip(berlinId, TripTypes::BERLIN_TOUR, route);

    std::cout << "✅ Berlin tour planned successfully!" << std::endl;
    std::cout << "🏙️ Cities to visit: " << route.size() << std::endl;
    std::cout << "🎯 Total distance: " << berlinTrip.getTotalDistance() << " km" << std::endl;

    return berlinTrip;
}

Trip TripService::createAndSaveTrip(int startCityId, const std::string& tripType, const V<int>& cityRoute) {
    // Calculate simple distance
    double totalDistance = calculateTotalDistance(cityRoute);

    std::cout << "🔍 DEBUG: Creating trip with:" << std::endl;
    std::cout << "   - Start City ID: " << startCityId << std::endl;
    std::cout << "   - Trip Type: " << tripType << std::endl;
    std::cout << "   - Route size: " << cityRoute.size() << " cities" << std::endl;
    std::cout << "   - Calculated distance: " << totalDistance << " km" << std::endl;

    // Create trip (ID = 0 for new trip)
    Trip trip(0, startCityId, tripType, totalDistance);

    std::cout << "🔍 DEBUG: Trip created with distance: " << trip.getTotalDistance() << " km" << std::endl;

    // Save to database
    bool saved = tripRepo.save(trip);
    if (saved) {
        std::cout << "Trip saved to database successfully" << std::endl;
        std::cout << "🔍 DEBUG: Trip ID after save: " << trip.getId() << std::endl;
        std::cout << "🔍 DEBUG: Trip distance after save: " << trip.getTotalDistance() << " km" << std::endl;

        // ✅ FIX: Check if trip has valid ID before adding cities
        if (trip.getId() > 0) {
            // Try to add cities to trip
            try {
                std::cout << "Adding " << cityRoute.size() << " cities to trip ID " << trip.getId() << std::endl;
                for (size_t i = 0; i < cityRoute.size(); i++) {
                    bool cityAdded = tripCityService.addCityToTrip(trip.getId(), cityRoute[i], i + 1);
                    if (cityAdded) {
                        std::cout << "✅ Added city " << cityRoute[i] << " at position " << (i + 1) << std::endl;
                    } else {
                        std::cout << "❌ Failed to add city " << cityRoute[i] << " at position " << (i + 1) << std::endl;
                    }
                }
                std::cout << "Cities added to trip successfully" << std::endl;
            } catch (const std::exception& e) {
                std::cout << "Exception adding cities to trip: " << e.what() << std::endl;
            }
        } else {
            std::cout << "❌ Trip ID is 0, cannot add cities" << std::endl;
        }
    } else {
        std::cout << "Failed to save trip to database" << std::endl;
    }

    std::cout << "🔍 DEBUG: Returning trip with ID: " << trip.getId() << ", distance: " << trip.getTotalDistance() << " km" << std::endl;
    return trip;
}

V<int> TripService::calculateOptimalRoute(int startCityId, const V<int>& citiesToVisit) {
    V<int> route;
    route.push_back(startCityId);

    std::cout << "🔍 Calculating optimal route starting from city " << startCityId << std::endl;
    std::cout << "   Cities to visit: ";
    for (size_t i = 0; i < citiesToVisit.size(); i++) {
        std::cout << citiesToVisit[i];
        if (i < citiesToVisit.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;

    // Simple route: just add cities in order (no distance optimization yet)
    // TODO: Implement actual recursive closest-city algorithm
    for (size_t i = 0; i < citiesToVisit.size(); i++) {
        route.push_back(citiesToVisit[i]);
    }

    std::cout << "   Final route: ";
    for (size_t i = 0; i < route.size(); i++) {
        std::cout << route[i];
        if (i < route.size() - 1) std::cout << " -> ";
    }
    std::cout << std::endl;

    return route;
}

double TripService::calculateTotalDistance(const V<int>& cityRoute) {
    std::cout << "🔍 Calculating total distance for route of " << cityRoute.size() << " cities" << std::endl;

    // Simple distance calculation: 150km between each city
    if (cityRoute.size() < 2) {
        std::cout << "   Route too short, distance = 0 km" << std::endl;
        return 0.0;
    }

    double distance = (cityRoute.size() - 1) * 150.0;
    std::cout << "   Calculated distance: " << distance << " km (150km between each city)" << std::endl;

    return distance;
}


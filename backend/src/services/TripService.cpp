#include "../../include/services/TripService.hpp"
#include "../../include/services/tripCityService.hpp"
#include "../../include/entities/CityDistance.hpp"
#include <iostream>
#include <iomanip>
#include <limits>


TripService::TripService(TripRepository& tripRepository, CityDistanceRepository& cityDistanceRepo, TripCityService& tripCityService)
    : tripRepo(tripRepository), cityDistanceRepo(cityDistanceRepo), tripCityService(tripCityService) {}

int TripService::findNearestUnvisitedCity(Trip& trip, int fromCityId) {
    auto distances = cityDistanceRepo.findByFromCity(fromCityId);
    int nearestCityId = -1;
    int minDistance = std::numeric_limits<int>::max();

    std::cout << "🔍 Finding nearest unvisited city from " << fromCityId << std::endl;

    for (const auto& row : distances) {
        int candidate = row.getToCityId();
        int distance = row.getDistance();

        // Skip the start city so we never return to the starting point
        if (candidate == trip.getStartCityId()) {
            std::cout << "   Skipping start city " << candidate << std::endl;
            continue;
        }

        // Check if city is already visited
        if (!hasCity(trip, candidate) && distance < minDistance) {
            minDistance = distance;
            nearestCityId = candidate;
            std::cout << "   New nearest: " << candidate << " (distance: " << distance << ")" << std::endl;
        } else {
            std::cout << "   Skipping " << candidate << " (visited or farther)" << std::endl;
        }
    }
    
    if (nearestCityId != -1) {
        std::cout << "✅ Nearest unvisited city: " << nearestCityId << " (distance: " << minDistance << ")" << std::endl;
    } else {
        std::cout << "❌ No unvisited cities found from " << fromCityId << std::endl;
    }
    
    return nearestCityId;
}

void TripService::CreateShortestTrip(Trip& trip, int startCityId) {
    std::cout << "\n CreateShortestTrip called with startCityId: " << startCityId << std::endl;
    
    // Check if we've reached the maximum cities (11 for now)
    int currentTripSize = getTripSize(trip);
    std::cout << "   Current trip size: " << currentTripSize << std::endl;
    
    if (currentTripSize >= 11) {
        std::cout << "✅ Trip complete! Visited 11 cities." << std::endl;
        return;
    }

    // Find the nearest unvisited city
    int nextCityId = findNearestUnvisitedCity(trip, startCityId);
    if (nextCityId == -1) {
        std::cout << "🏁 No more cities to visit. Trip complete!" << std::endl;
        return;
    }

    // Get distance to next city and update total distance
    int legDistance = cityDistanceRepo.getDistance(startCityId, nextCityId);
    if (legDistance > 0) {
        trip.setTotalDistance(trip.getTotalDistance() + legDistance);
        std::cout << "📏 Added " << legDistance << " km to trip. Total: " << trip.getTotalDistance() << " km" << std::endl;
    }

    // Add city to trip
    addCityToTrip(trip, nextCityId);

    // Recursive call with the new city as starting point
    CreateShortestTrip(trip, nextCityId);
}

// Add this overloaded method
void TripService::CreateShortestTrip(Trip& trip, int startCityId, const V<int>& allowedCities) {
    std::cout << "\n CreateShortestTrip called with startCityId: " << startCityId << std::endl;
    
    // ✅ FIXED: Check if we've visited all allowed cities (flexible limit)
    int currentTripSize = getTripSize(trip);
    int targetCities = allowedCities.size() + 1; // +1 for the starting city
    std::cout << "   Current trip size: " << currentTripSize << std::endl;
    std::cout << "   Target cities: " << targetCities << std::endl;
    std::cout << "   Allowed cities count: " << allowedCities.size() << std::endl;
    
    // ✅ FIXED: Use dynamic limit based on allowed cities, not hardcoded 11
    if (currentTripSize >= targetCities) {
        std::cout << "✅ Trip complete! Visited all " << targetCities << " cities." << std::endl;
        return;
    }

    // Find the nearest unvisited city from the allowed cities only
    int nextCityId = findNearestUnvisitedCityFromList(trip, startCityId, allowedCities);
    std::cout << "   Next city found: " << nextCityId << std::endl;
    
    if (nextCityId == -1) {
        std::cout << " No more allowed cities to visit. Trip complete!" << std::endl;
        std::cout << "   Final trip size: " << currentTripSize << std::endl;
        return;
    }

    // Get distance to next city and update total distance
    int legDistance = cityDistanceRepo.getDistance(startCityId, nextCityId);
    if (legDistance > 0) {
        trip.setTotalDistance(trip.getTotalDistance() + legDistance);
        std::cout << " Distance from " << startCityId << " to " << nextCityId << ": " << legDistance << " km" << std::endl;
        std::cout << " Added " << legDistance << " km to trip. Total: " << trip.getTotalDistance() << " km" << std::endl;
    }

    // Add city to trip
    addCityToTrip(trip, nextCityId);

    // Recursive call with the new city as starting point
    CreateShortestTrip(trip, nextCityId, allowedCities);
}

// Add helper method to find nearest city from a specific list
int TripService::findNearestUnvisitedCityFromList(Trip& trip, int fromCityId, const V<int>& allowedCities) {
    auto distances = cityDistanceRepo.findByFromCity(fromCityId);
    int nearestCityId = -1;
    int minDistance = std::numeric_limits<int>::max();

    std::cout << "🔍 Finding nearest unvisited city from allowed list" << std::endl;

    for (const auto& row : distances) {
        int candidate = row.getToCityId();
        int distance = row.getDistance();

        // Skip if not in allowed cities list
        bool isAllowed = false;
        for (int allowedCity : allowedCities) {
            if (candidate == allowedCity) {
                isAllowed = true;
                break;
            }
        }
        
        if (!isAllowed) {
            continue; // Skip cities not in the allowed list
        }

        // Skip the start city
        if (candidate == trip.getStartCityId()) {
            continue;
        }

        // Check if city is already visited
        if (!hasCity(trip, candidate) && distance < minDistance) {
            minDistance = distance;
            nearestCityId = candidate;
        }
    }
    
    return nearestCityId;
}

// Helper methods that were in Trip entity but should be in service
bool TripService::hasCity(const Trip& trip, int cityId) {
    // Check if city is already in the trip_cities table
    V<TripCity> tripCities = tripCityService.getCitiesForTrip(trip.getId());
    
    for (const auto& tripCity : tripCities) {
        if (tripCity.getCityId() == cityId) {
            return true;
        }
    }
    return false;
}

int TripService::getTripSize(const Trip& trip) {
    // Get the number of cities in the trip
    V<TripCity> tripCities = tripCityService.getCitiesForTrip(trip.getId());
    return tripCities.size();
}

void TripService::addCityToTrip(Trip& trip, int cityId) {
    // Add city to trip_cities table
    int visitOrder = getTripSize(trip) + 1; // Next position
    bool success = tripCityService.addCityToTrip(trip.getId(), cityId, visitOrder);
    
    if (success) {
        std::cout << "✅ Added city " << cityId << " to trip at position " << visitOrder << std::endl;
    } else {
        std::cout << "❌ Failed to add city " << cityId << " to trip" << std::endl;
    }
}

// Main trip planning methods using the new recursive approach
Trip TripService::planParisTour() {
    std::cout << "\n Planning Paris Tour - Visiting Initial 11 European Cities\n" << std::endl;

    // Create trip - Paris is city ID 9
    Trip parisTrip(0, 9, "paris_tour", 0.0);
    
    // Save trip to get ID
    bool saved = tripRepo.save(parisTrip);
    if (!saved || parisTrip.getId() <= 0) {
        std::cout << "❌ Failed to save Paris trip" << std::endl;
        return parisTrip;
    }

    std::cout << "✅ Created Paris trip with ID: " << parisTrip.getId() << std::endl;

    // Add Paris as the first city
    addCityToTrip(parisTrip, 9); // Paris is city ID 9

    // Include all initial 11 cities (exclude Stockholm=12 and Vienna=13)
    V<int> initialCities;
    initialCities.push_back(1);  // Amsterdam
    initialCities.push_back(2);  // Berlin
    initialCities.push_back(3);  // Brussels
    initialCities.push_back(4);  // Budapest
    initialCities.push_back(5);  // Hamburg
    initialCities.push_back(6);  // Lisbon
    initialCities.push_back(7);  // London
    initialCities.push_back(8);  // Madrid
    initialCities.push_back(10); // Prague
    initialCities.push_back(11); // Rome
    // Note: Paris (9) is already added as the starting city
    // Excluding: Stockholm (12) and Vienna (13)

    // Show what cities we're trying to visit
    std::cout << " DEBUG: Initial cities list: ";
    for (size_t i = 0; i < initialCities.size(); i++) {
        std::cout << initialCities[i];
        if (i < initialCities.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;

    std::cout << " Planning route to visit " << (initialCities.size() + 1) << " cities total (initial 11):" << std::endl;
    std::cout << "   - Starting city: Paris (ID 9)" << std::endl;
    std::cout << "   - Other cities to visit: " << initialCities.size() << std::endl;
    std::cout << "   - Excluding: Stockholm (ID 12) and Vienna (ID 13)" << std::endl;

    // Use recursive algorithm to find optimal route among initial cities only
    CreateShortestTrip(parisTrip, 9, initialCities);

    std::cout << " Paris tour completed!" << std::endl;
    std::cout << "   Total distance: " << parisTrip.getTotalDistance() << " km" << std::endl;
    std::cout << "   Cities visited: " << getTripSize(parisTrip) << std::endl;

    return parisTrip;
}

Trip TripService::planLondonTour(int numCities) {
    std::cout << "\n🇬🇧 Planning London Tour for " << numCities << " cities\n" << std::endl;

    Trip londonTrip(0, 7, "london_tour", 0.0); // London has ID 7
    
    bool saved = tripRepo.save(londonTrip);
    if (!saved || londonTrip.getId() <= 0) {
        std::cout << "❌ Failed to save London trip" << std::endl;
        return londonTrip;
    }

    std::cout << "✅ Created London trip with ID: " << londonTrip.getId() << std::endl;

    // Add London as the first city
    addCityToTrip(londonTrip, 7); // London is city ID 7

    //  Only visit the specified number of cities (excluding London)
    V<int> availableCities;
    availableCities.push_back(1);  // Amsterdam
    availableCities.push_back(2);  // Berlin
    availableCities.push_back(3);  // Brussels
    availableCities.push_back(4);  // Budapest
    availableCities.push_back(5);  // Hamburg
    availableCities.push_back(6);  // Lisbon
    availableCities.push_back(8);  // Madrid
    availableCities.push_back(9);  // Paris
    availableCities.push_back(10); // Prague
    availableCities.push_back(11); // Rome
    availableCities.push_back(12); // Stockholm
    availableCities.push_back(13); // Vienna
    // Note: London (7) is already added as the starting city

    // ✅ NEW: Limit to the requested number of cities (excluding London)
    int citiesToVisit = std::min(numCities - 1, (int)availableCities.size());
    V<int> selectedCities;
    for (int i = 0; i < citiesToVisit; i++) {
        selectedCities.push_back(availableCities[i]);
    }

    std::cout << " Planning London route to visit " << (selectedCities.size() + 1) << " cities total:" << std::endl;
    std::cout << "   - Starting city: London (ID 7)" << std::endl;
    std::cout << "   - Other cities to visit: " << selectedCities.size() << std::endl;

    // Use recursive algorithm to find optimal route
    CreateShortestTrip(londonTrip, 7, selectedCities);

    std::cout << " London tour completed!" << std::endl;
    std::cout << "   Total distance: " << londonTrip.getTotalDistance() << " km" << std::endl;
    std::cout << "   Cities visited: " << getTripSize(londonTrip) << std::endl;

    return londonTrip;
}

Trip TripService::planBerlinTour() {
    std::cout << "\n🇩🇪 Planning Berlin Tour\n" << std::endl;

    Trip berlinTrip(0, 2, "berlin_tour", 0.0); // Berlin has ID 2
    
    bool saved = tripRepo.save(berlinTrip);
    if (!saved || berlinTrip.getId() <= 0) {
        std::cout << "❌ Failed to save Berlin trip" << std::endl;
        return berlinTrip;
    }

    std::cout << "✅ Created Berlin trip with ID: " << berlinTrip.getId() << std::endl;

    // Add Berlin as the first city
    addCityToTrip(berlinTrip, 2); // Berlin is city ID 2

    // Berlin tour should visit ALL 13 European cities
    V<int> allEuropeanCities;
    allEuropeanCities.push_back(1);  // Amsterdam
    allEuropeanCities.push_back(3);  // Brussels
    allEuropeanCities.push_back(4);  // Budapest
    allEuropeanCities.push_back(5);  // Hamburg
    allEuropeanCities.push_back(6);  // Lisbon
    allEuropeanCities.push_back(7);  // London
    allEuropeanCities.push_back(8);  // Madrid
    allEuropeanCities.push_back(9);  // Paris
    allEuropeanCities.push_back(10); // Prague
    allEuropeanCities.push_back(11); // Rome
    allEuropeanCities.push_back(12); // Stockholm
    allEuropeanCities.push_back(13); // Vienna

    std::cout << " Planning Berlin route to visit ALL " << (allEuropeanCities.size() + 1) << " European cities:" << std::endl;
    std::cout << "   - Starting city: Berlin (ID 2)" << std::endl;
    std::cout << "   - Other cities to visit: " << allEuropeanCities.size() << std::endl;

    // Use recursive algorithm to find optimal route
    CreateShortestTrip(berlinTrip, 2, allEuropeanCities);

    std::cout << " Berlin tour completed!" << std::endl;
    std::cout << "   Total distance: " << berlinTrip.getTotalDistance() << " km" << std::endl;
    std::cout << "   Cities visited: " << getTripSize(berlinTrip) << std::endl;

    return berlinTrip;
}

Trip TripService::planCustomTour(int startCityId, const V<int>& citiesToVisit) {
    std::cout << "\n Planning Custom Tour\n" << std::endl;
    std::cout << "   Starting city ID: " << startCityId << std::endl;
    std::cout << "   Cities to visit: " << citiesToVisit.size() << std::endl;

    Trip customTrip(0, startCityId, "custom", 0.0);
    
    bool saved = tripRepo.save(customTrip);
    if (!saved || customTrip.getId() <= 0) {
        std::cout << "❌ Failed to save custom trip" << std::endl;
        return customTrip;
    }

    std::cout << "✅ Created custom trip with ID: " << customTrip.getId() << std::endl;

    // Add starting city as the first city
    addCityToTrip(customTrip, startCityId);

    std::cout << " Planning custom route:" << std::endl;
    std::cout << "   - Starting city: " << startCityId << std::endl;
    std::cout << "   - Cities to visit: " << citiesToVisit.size() << std::endl;

    // Use recursive algorithm with user-selected cities
    CreateShortestTrip(customTrip, startCityId, citiesToVisit);

    std::cout << " Custom tour completed!" << std::endl;
    std::cout << "   Total distance: " << customTrip.getTotalDistance() << " km" << std::endl;
    std::cout << "   Cities visited: " << getTripSize(customTrip) << std::endl;

    return customTrip;
}


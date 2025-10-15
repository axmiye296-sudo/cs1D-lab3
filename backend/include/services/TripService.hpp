/**
 * @file TripService.hpp
 * @brief Service class for Trip planning and management operations
 */

 #ifndef TRIP_SERVICE_HPP
 #define TRIP_SERVICE_HPP
 
 #include "../header.hpp"
 #include "../entities/Trip.hpp"
 #include "../entities/TripCity.hpp"
 #include "../repositories/TripRepository.hpp"
 #include "../repositories/CityDistanceRepository.hpp"
 #include "../services/tripCityService.hpp"
 
 class CityService;
 
 /**
  * @class TripService
  * @brief Handles trip planning and management business logic
  * 
  * The TripService class provides high-level trip planning functionality,
  * including predefined tours and custom trip creation. It coordinates
  * between repositories and services to create optimal travel itineraries.
  */
 class TripService {
 private:
     TripRepository& tripRepo;              ///< Repository for trip data access
     CityDistanceRepository& cityDistanceRepo; ///< Repository for distance calculations
     TripCityService& tripCityService;      ///< Service for trip-city relationships
     CityService& cityService;              ///< Service for city operations
 
     // Helper methods for trip planning
     /**
      * @brief Check if a city is already in a trip
      * @param trip The trip to check
      * @param cityId The city ID to check for
      * @return True if city is in trip, false otherwise
      * 
      * Determines whether a specific city is already included in the trip.
      */
     bool hasCity(const Trip& trip, int cityId);
     
     /**
      * @brief Get the number of cities in a trip
      * @param trip The trip to check
      * @return The number of cities in the trip
      * 
      * Returns the count of cities currently in the trip.
      */
     int getTripSize(const Trip& trip);
     
     /**
      * @brief Add a city to a trip
      * @param trip The trip to modify
      * @param cityId The city ID to add
      * 
      * Adds a city to the trip's itinerary.
      */
     void addCityToTrip(Trip& trip, int cityId);
 
     // Recursive trip planning algorithms
     /**
      * @brief Find the nearest unvisited city
      * @param trip The current trip
      * @param fromCityId The current city ID
      * @return The ID of the nearest unvisited city, or -1 if none found
      * 
      * Uses distance calculations to find the closest city that hasn't been visited yet.
      */
     int findNearestUnvisitedCity(Trip& trip, int fromCityId);
     
     /**
      * @brief Create the shortest possible trip
      * @param trip The trip to populate
      * @param startCityId The starting city ID
      * 
      * Creates an optimal trip using the nearest neighbor algorithm.
      */
     void CreateShortestTrip(Trip& trip, int startCityId);
     
     /**
      * @brief Create the shortest trip with city restrictions
      * @param trip The trip to populate
      * @param startCityId The starting city ID
      * @param allowedCities Vector of allowed city IDs
      * 
      * Creates an optimal trip using only the specified cities.
      */
     void CreateShortestTrip(Trip& trip, int startCityId, const V<int>& allowedCities);
     
     /**
      * @brief Find nearest unvisited city from a restricted list
      * @param trip The current trip
      * @param fromCityId The current city ID
      * @param allowedCities Vector of allowed city IDs
      * @return The ID of the nearest allowed unvisited city, or -1 if none found
      * 
      * Finds the closest city from a restricted list that hasn't been visited yet.
      */
     int findNearestUnvisitedCityFromList(Trip& trip, int fromCityId, const V<int>& allowedCities);
 
 public:
     /**
      * @brief Constructor
      * @param tripRepository Reference to TripRepository instance
      * @param cityDistanceRepo Reference to CityDistanceRepository instance
      * @param tripCityService Reference to TripCityService instance
      * @param cityService Reference to CityService instance
      * 
      * Initializes the service with required repositories and services.
      */
     TripService(TripRepository& tripRepository, CityDistanceRepository& cityDistanceRepo, TripCityService& tripCityService, CityService& cityService);
     
     // Main trip planning methods
     /**
      * @brief Plan a Paris tour
      * @return Trip object representing the Paris tour
      * 
      * Creates a predefined tour of Paris with optimal city ordering.
      */
     Trip planParisTour();
     
     /**
      * @brief Plan a London tour
      * @param numCities Number of cities to include (default: 13)
      * @return Trip object representing the London tour
      * 
      * Creates a predefined tour of London with the specified number of cities.
      */
     Trip planLondonTour(int numCities = 13);
     
     /**
      * @brief Plan a custom tour
      * @param startCityId The ID of the starting city
      * @param citiesToVisit Vector of city IDs to visit
      * @return Trip object representing the custom tour
      * 
      * Creates a custom tour starting from the specified city and visiting
      * the provided list of cities in optimal order.
      */
     Trip planCustomTour(int startCityId, const V<int>& citiesToVisit);
     
     /**
      * @brief Plan a Berlin tour
      * @return Trip object representing the Berlin tour
      * 
      * Creates a predefined tour of Berlin with optimal city ordering.
      */
     Trip planBerlinTour();
 };
 
 #endif
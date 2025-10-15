/**
 * @file Trip.hpp
 * @brief Trip entity class representing a travel itinerary
 */

 #ifndef TRIP_HPP
 #define TRIP_HPP
 
 #include "../header.hpp"
 
 /**
  * @class Trip
  * @brief Represents a travel itinerary with cities and routing information
  * 
  * The Trip class encapsulates information about a travel itinerary, including
  * the starting city, trip type, total distance, and associated cities.
  * It serves as the main data model for trip planning functionality.
  */
 class Trip {
 private:
     int id;                    ///< Unique identifier for the trip
     int start_city_id;         ///< ID of the starting city for the trip
     std::string trip_type;     ///< Type of trip (e.g., "paris_tour", "custom_tour")
     double total_distance;     ///< Total distance of the trip in kilometers
 
 public:
     // Constructors
     /**
      * @brief Default constructor
      * 
      * Creates an empty Trip object with default values.
      */
     Trip();
     
     /**
      * @brief Full constructor with all parameters
      * @param id Unique identifier for the trip
      * @param start_city_id ID of the starting city
      * @param trip_type Type of the trip
      * @param total_distance Total distance of the trip
      * 
      * Creates a Trip object with all specified values.
      */
     Trip(int id, int start_city_id, std::string trip_type, double total_distance);
     
     /**
      * @brief Constructor for new trips (without ID)
      * @param start_city_id ID of the starting city
      * @param trip_type Type of the trip
      * @param total_distance Total distance of the trip
      * 
      * Creates a Trip object for new trips where ID will be auto-generated.
      */
     Trip(int start_city_id, std::string trip_type, double total_distance);
 
     // Getters
     /**
      * @brief Get the trip ID
      * @return The unique identifier for the trip
      */
     int getId() const;
     
     /**
      * @brief Get the starting city ID
      * @return The ID of the starting city
      */
     int getStartCityId() const;
     
     /**
      * @brief Get the trip type
      * @return The type of the trip
      */
     std::string getTripType() const;
     
     /**
      * @brief Get the total distance
      * @return The total distance of the trip in kilometers
      */
     double getTotalDistance() const;
 
     // Setters
     /**
      * @brief Set the trip ID
      * @param id The new trip ID
      */
     void setId(int id);
     
     /**
      * @brief Set the starting city ID
      * @param start_city_id The new starting city ID
      */
     void setStartCityId(int start_city_id);
     
     /**
      * @brief Set the trip type
      * @param trip_type The new trip type
      */
     void setTripType(std::string trip_type);
     
     /**
      * @brief Set the total distance
      * @param total_distance The new total distance
      */
     void setTotalDistance(double total_distance);
 
     // Validation
     /**
      * @brief Validate if the trip has valid data
      * @return True if the trip is valid, false otherwise
      * 
      * Checks if all required fields have valid values.
      */
     bool isValid() const;
 
     // Utility methods
     /**
      * @brief Convert trip to string representation
      * @return Formatted string representation of the trip
      * 
      * Creates a human-readable string representation of the trip.
      */
     std::string toString() const;
     
     /**
      * @brief Compare two trips for equality
      * @param other The other trip to compare with
      * @return True if trips are equal, false otherwise
      * 
      * Compares all fields of two Trip objects for equality.
      */
     bool equals(const Trip& other) const;
 
     // Trip planning methods
     /**
      * @brief Check if a city is included in this trip
      * @param cityId The city ID to check
      * @return True if city is in the trip, false otherwise
      * 
      * Determines whether a specific city is part of this trip's itinerary.
      */
     bool hasCity(int cityId) const;
     
     /**
      * @brief Get the number of cities in this trip
      * @return The number of cities in the trip
      * 
      * Returns the count of cities included in this trip.
      */
     int getTripSize() const;
     
     /**
      * @brief Add a city to the trip
      * @param trip Reference to the trip to modify
      * @param cityId ID of the city to add
      * 
      * Adds a city to the trip's itinerary by creating a TripCity relationship.
      */
     void addTC(Trip& trip, int cityId);
 };
 
 #endif
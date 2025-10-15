/**
 * ENTITY LAYER: TripCity class
 */
#ifndef TRIP_CITY_HPP
#define TRIP_CITY_HPP

#include "header.hpp"
#include <string>
#include <memory>

// Forward declaration
class TripCityRepository;

/**
 * @class TripCity
 * @brief Represents the relationship between a trip and a city with visit order
 * 
 * This class models the many-to-many relationship between trips and cities,
 * storing the visit order to determine the sequence of cities in a trip.
 */
class TripCity {
private:
    int id;         ///< Unique identifier in the database
    int tripId;     ///< ID of the trip this city belongs to
    int cityId;     ///< ID of the city being visited
    int visitOrder; ///< Order of visit in the trip (1st, 2nd, 3rd, etc.)

public:
    /**
     * @brief Default constructor
     * 
     * Creates an empty TripCity object with all fields initialized to 0.
     */
    TripCity();
    
    /**
     * @brief Full constructor with all parameters
     * @param id Unique database identifier
     * @param tripId ID of the trip
     * @param cityId ID of the city
     * @param visitOrder Order of visit in the trip
     */
    TripCity(int id, int tripId, int cityId, int visitOrder);
    
    /**
     * @brief Constructor for new records (without ID)
     * @param tripId ID of the trip
     * @param cityId ID of the city
     * @param visitOrder Order of visit in the trip
     */
    TripCity(int tripId, int cityId, int visitOrder);

    // Getters
    /**
     * @brief Get the unique database ID
     * @return The database ID
     */
    int getId() const;
    
    /**
     * @brief Get the trip ID
     * @return The trip ID this city belongs to
     */
    int getTripId() const;
    
    /**
     * @brief Get the city ID
     * @return The city ID being visited
     */
    int getCityId() const;
    
    /**
     * @brief Get the visit order
     * @return The order of visit in the trip
     */
    int getVisitOrder() const;

    // Setters
    /**
     * @brief Set the database ID
     * @param id The new database ID
     */
    void setId(int id);
    
    /**
     * @brief Set the trip ID
     * @param tripId The new trip ID
     */
    void setTripId(int tripId);
    
    /**
     * @brief Set the city ID
     * @param cityId The new city ID
     */
    void setCityId(int cityId);
    
    /**
     * @brief Set the visit order
     * @param visitOrder The new visit order
     */
    void setVisitOrder(int visitOrder);

    // Validation
    /**
     * @brief Validate if the TripCity object has valid data
     * @return true if all fields are valid (positive values), false otherwise
     */
    bool isValid() const;

    // Utility methods
    /**
     * @brief Convert TripCity to string representation
     * @return Formatted string representation of the object
     */
    std::string toString() const;
    
    /**
     * @brief Compare two TripCity objects for equality
     * @param other The other TripCity object to compare with
     * @return true if all fields match, false otherwise
     */
    bool equals(const TripCity& other) const;
};

#endif
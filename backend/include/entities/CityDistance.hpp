/**
 * @file CityDistance.hpp
 * @brief CityDistance entity class representing distance between two cities
 */

 #ifndef CITY_DISTANCE_HPP
 #define CITY_DISTANCE_HPP
 
 /**
  * @class CityDistance
  * @brief Represents the distance relationship between two cities
  * 
  * The CityDistance class models the distance between two cities in the trip planning system.
  * It stores the source city ID, destination city ID, and the distance between them.
  * This information is used for calculating trip distances and finding optimal routes.
  */
 class CityDistance {
 private:
     int fromCityId;  ///< ID of the source city
     int toCityId;    ///< ID of the destination city
     int distance;    ///< Distance between the cities (in kilometers)
 
 public:
     /**
      * @brief Default constructor
      * 
      * Creates an empty CityDistance object with all fields set to 0.
      */
     CityDistance();
     
     /**
      * @brief Parameterized constructor
      * @param fromCityId ID of the source city
      * @param toCityId ID of the destination city
      * @param distance Distance between the cities
      * 
      * Creates a CityDistance object with the specified values.
      */
     CityDistance(int fromCityId, int toCityId, int distance);
 
     // Getters
     /**
      * @brief Get the source city ID
      * @return The ID of the source city
      */
     int getFromCityId() const;
     
     /**
      * @brief Get the destination city ID
      * @return The ID of the destination city
      */
     int getToCityId() const;
     
     /**
      * @brief Get the distance between cities
      * @return The distance in kilometers
      */
     int getDistance() const;
 
     // Setters
     /**
      * @brief Set the source city ID
      * @param fromCityId The new source city ID
      */
     void setFromCityId(int fromCityId);
     
     /**
      * @brief Set the destination city ID
      * @param toCityId The new destination city ID
      */
     void setToCityId(int toCityId);
     
     /**
      * @brief Set the distance between cities
      * @param distance The new distance in kilometers
      */
     void setDistance(int distance);
 };
 
 #endif
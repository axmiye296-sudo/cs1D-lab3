/**
 * @file City.hpp
 * @brief City entity class representing a travel destination
 */

 #ifndef CITY_HPP
 #define CITY_HPP
 
 #include "../header.hpp"
 
 /**
  * @class City
  * @brief Represents a city in the trip planning system
  * 
  * The City class encapsulates information about travel destinations,
  * including unique identification and name. It serves as a data model
  * for the trip planning application.
  */
 class City {
 private:
     int id;              ///< Unique identifier for the city
     std::string name;    ///< Name of the city
 
 public:
     /**
      * @brief Default constructor
      * 
      * Creates an empty City object with id = 0 and empty name.
      */
     City();
     
     /**
      * @brief Parameterized constructor
      * @param id The unique identifier for the city
      * @param name The name of the city
      * 
      * Creates a City object with the specified ID and name.
      */
     City(int id, const std::string& name);
 
     // Getters
     /**
      * @brief Get the city's unique identifier
      * @return The city's ID number
      */
     int getId() const;
     
     /**
      * @brief Get the city's name
      * @return The city's name as a string
      */
     std::string getName() const;
 
     // Setters
     /**
      * @brief Set the city's unique identifier
      * @param id The new ID for the city
      */
     void setId(int id);
     
     /**
      * @brief Set the city's name
      * @param name The new name for the city
      */
     void setName(const std::string& name);
 
     /**
      * @brief Print city information
      * 
      * Displays the city's ID and name to the console.
      * Used for debugging and information display purposes.
      */
     void print() const;
 };
 
 #endif
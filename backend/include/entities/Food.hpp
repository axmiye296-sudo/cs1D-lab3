/**
 * @file Food.hpp
 * @brief Food entity class representing food recommendations for cities
 */

 #ifndef FOOD_HPP
 #define FOOD_HPP
 
 #include "../header.hpp"
 
 /**
  * @class Food
  * @brief Represents a food recommendation associated with a specific city
  * 
  * The Food class encapsulates information about food recommendations,
  * including the food name, associated city, and price. This helps users
  * discover local cuisine when planning their trips.
  */
 class Food {
 private:
     int id;              ///< Primary key - unique identifier for each food item
     std::string name;    ///< Food name - the actual name like "Croissant"
     int cityId;          ///< Foreign key - which city this food belongs to
     double price;        ///< Food price - the cost like 2.50
 
 public:
     /**
      * @brief Default constructor
      * 
      * Creates an empty Food object with default values.
      */
     Food();
     
     /**
      * @brief Parameterized constructor
      * @param id Unique identifier for the food item
      * @param name Name of the food item
      * @param cityId ID of the city this food belongs to
      * @param price Price of the food item
      * 
      * Creates a Food object with the specified values.
      */
     Food(int id, const std::string& name, int cityId, double price);
 
     // Getters
     /**
      * @brief Get the food item ID
      * @return The unique identifier for the food item
      */
     int getId() const;
     
     /**
      * @brief Get the food name
      * @return The name of the food item
      */
     std::string getName() const;
     
     /**
      * @brief Get the associated city ID
      * @return The ID of the city this food belongs to
      */
     int getCityId() const;
     
     /**
      * @brief Get the food price
      * @return The price of the food item
      */
     double getPrice() const;
 
     // Setters
     /**
      * @brief Set the food item ID
      * @param id The new unique identifier
      */
     void setId(int id);
     
     /**
      * @brief Set the food name
      * @param name The new food name
      */
     void setName(const std::string& name);
     
     /**
      * @brief Set the associated city ID
      * @param cityId The new city ID
      */
     void setCityId(int cityId);
     
     /**
      * @brief Set the food price
      * @param price The new price
      */
     void setPrice(double price);
 
     /**
      * @brief Print food information
      * 
      * Displays the food item's details to the console.
      * Used for debugging and information display purposes.
      */
     void print() const;
 };
 
 #endif
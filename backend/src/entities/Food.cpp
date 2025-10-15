/**
 * @file Food.cpp
 * @brief Implementation of Food entity class
 */

#include "../../include/entities/Food.hpp"

// ============================================================================
// CONSTRUCTORS
// ============================================================================

/**
 * @brief Default constructor implementation
 * 
 * Creates an empty Food object with:
 * - ID: 0
 * - Name: empty string
 * - City ID: 0
 * - Price: 0.0
 */
Food::Food() : id(0), name(""), cityId(0), price(0.0) {
}

/**
 * @brief Parameterized constructor implementation
 * @param id The unique identifier for the food item
 * @param name The name of the food item
 * @param cityId The ID of the city this food belongs to
 * @param price The price of the food item
 * 
 * Creates a Food object with the specified values.
 */
Food::Food(int id, const std::string& name, int cityId, double price)
    : id(id), name(name), cityId(cityId), price(price) {
}

// ============================================================================
// GETTERS
// ============================================================================

/**
 * @brief Get the food item ID
 * @return The unique identifier for the food item
 */
int Food::getId() const {
    return id;
}

/**
 * @brief Get the food name
 * @return The name of the food item
 */
std::string Food::getName() const {
    return name;
}

/**
 * @brief Get the associated city ID
 * @return The ID of the city this food belongs to
 */
int Food::getCityId() const {
    return cityId;
}

/**
 * @brief Get the food price
 * @return The price of the food item
 */
double Food::getPrice() const {
    return price;
}

// ============================================================================
// SETTERS
// ============================================================================

/**
 * @brief Set the food item ID
 * @param id The new unique identifier
 */
void Food::setId(int id) {
    this->id = id;
}

/**
 * @brief Set the food name
 * @param name The new food name
 */
void Food::setName(const std::string& name) {
    this->name = name;
}

/**
 * @brief Set the associated city ID
 * @param cityId The new city ID
 */
void Food::setCityId(int cityId) {
    this->cityId = cityId;
}

/**
 * @brief Set the food price
 * @param price The new price
 */
void Food::setPrice(double price) {
    this->price = price;
}

// ============================================================================
// DISPLAY METHODS
// ============================================================================

/**
 * @brief Print food information
 * 
 * Displays the food item's details to the console in a formatted manner.
 * Used for debugging and information display purposes.
 * 
 * Example output: "  - Croissant (€2.50)"
 */
void Food::print() const {
    std::cout << "  - " << name << " (€" << std::fixed << std::setprecision(2) << price << ")" << std::endl;
    // Example output: "  - Croissant (€2.50)"
}
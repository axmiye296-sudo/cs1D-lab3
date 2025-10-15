/**
 * @file City.cpp
 * @brief Implementation of City entity class
 */

#include "../../include/entities/City.hpp"

// ============================================================================
// CONSTRUCTORS
// ============================================================================

/**
 * @brief Default constructor implementation
 * 
 * Creates an empty City object with:
 * - ID: 0
 * - Name: empty string
 */
City::City() : id(0), name("") {
}

/**
 * @brief Parameterized constructor implementation
 * @param id The unique identifier for the city
 * @param name The name of the city
 * 
 * Creates a City object with the specified ID and name.
 */
City::City(int id, const std::string& name) : id(id), name(name) {
}

// ============================================================================
// GETTERS
// ============================================================================

/**
 * @brief Get the city's unique identifier
 * @return The city's ID number
 */
int City::getId() const {
    return id;
}

/**
 * @brief Get the city's name
 * @return The city's name as a string
 */
std::string City::getName() const {
    return name;
}

// ============================================================================
// SETTERS
// ============================================================================

/**
 * @brief Set the city's unique identifier
 * @param id The new ID for the city
 */
void City::setId(int id) {
    this->id = id;
}

/**
 * @brief Set the city's name
 * @param name The new name for the city
 */
void City::setName(const std::string& name) {
    this->name = name;
}

// ============================================================================
// DISPLAY METHODS
// ============================================================================

/**
 * @brief Print city information
 * 
 * Displays the city's ID and name to the console.
 * Used for debugging and information display purposes.
 * 
 * Example output: "ID: 1, Name: Paris"
 */
void City::print() const {
    std::cout << "ID: " << id << ", Name: " << name << std::endl;
    // Example output: "ID: 1, Name: Paris"
}
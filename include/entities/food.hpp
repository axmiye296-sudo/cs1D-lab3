#ifndef FOOD_HPP
#define FOOD_HPP

#include "../header.hpp"

class Food {
private:
    int id;                 // Primary key from foods table - unique identifier for each food
    std::string name;       // Food name from foods table - e.g. "Croissant"
    int cityId;             // Foreign key - which city this food belongs to (links to cities table)
    double price;           // Food price from foods table - the cost like 2.50

public:
// Constructors and Destructors
    Food();
    Food(int id, const std::string& name, int cityId, double price);
    ~Food();

// Getter functions
    int getId() const;
    std::string getName() const;
    int getCityId() const;
    double getPrice() const;

// Setter functions
    void setId(int id);
    void setName(const std::string& name);
    void setCityId(int cityId);
    void setPrice(double price);

// Display function
    void print() const;
};

#endif // FOOD_HPP


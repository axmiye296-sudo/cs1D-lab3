#ifndef FOOD_HPP
#define FOOD_HPP

#include "../header.hpp"

class Food {
private:
    int id;              // Primary key from foods table - unique identifier for each food
    std::string name;    // Food name from foods table - the actual name like "Croissant"
    int cityId;          // Foreign key - which city this food belongs to (links to cities table)
    double price;        // Food price from foods table - the cost like 2.50

public:
    Food();
    Food(int id, const std::string& name, int cityId, double price);

    int getId() const;
    std::string getName() const;
    int getCityId() const;
    double getPrice() const;

    void setId(int id);
    void setName(const std::string& name);
    void setCityId(int cityId);
    void setPrice(double price);

    void print() const;
};

#endif
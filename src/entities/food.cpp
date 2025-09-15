#include "food.hpp"

Food::Food() {}

Food::~Food() {}

Food::Food(int id, const std::string& name, int cityId, double price) 
    : id(id), name(name), cityId(cityId), price(price) {}

// Getter functions
    int Food::getId() const   
    { return id; }

    std::string Food::getName() const 
    { return name; }

    int Food::getCityId() const
    { return cityId; }

    double Food::getPrice() const
    { return price; }

// Setter functions
    void Food::setId(int id)
    { this->id = id; }

    void Food::setName(const std::string& name)
    { this->name = name; }

    void Food::setCityId(int cityId)
    { this->cityId = cityId; }

    void Food::setPrice(double price)
    { this->price = price; }

// Display function
    void Food::print() const
    {
        std::cout << "Food ID: " << id << "\n"
                  << "Name: " << name << "\n"
                  << "City ID: " << cityId << "\n"
                  << "Price: $" << price << "\n";
    }
    

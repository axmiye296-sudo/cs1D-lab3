/// @brief Purchase Implementation file
 #include "Purchase.hpp"
 
/// @brief Constructor & Destructor Implementations
    Purchase::Purchase() {}
    Purchase::Purchase(int id, int cityID, int foodID, int quantity, int tripID)
                       : id(id), cityID(cityID), foodID(foodID), 
                       quantity(quantity), tripID(tripID) {}
    Purchase::~Purchase() {}

/// @brief Get Function Implementations 
    int Purchase::getID()
    {
        return id;
    }
    int Purchase::getCityID()
    {
        return cityID;
    }
    int Purchase::getFoodID()
    {
        return foodID;
    }
    int Purchase::getQuantity()
    {
        return quantity;
    }
    int Purchase::getTripID()
    {
        return tripID;
    }

/// @brief Set Function Declarations
    void Purchase::setID(int id) 
    {
        this->id = id;
    }
    void Purchase::setCityID(int cityID) 
    {
        this->cityID = cityID;
    }
    void Purchase::setFoodID(int foodID) 
    {
        this->foodID = foodID;
    }
    void Purchase::setQuantity(int quantity) 
    {
        this->quantity = quantity;
    }
    void Purchase::setTripID(int tripID) 
    {
        this->tripID = tripID;
    }


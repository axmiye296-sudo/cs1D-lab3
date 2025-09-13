/// @brief Purchase Header file

#pragma once

#include "header.hpp"

/// @class Purchase

    class Purchase
    {
    private:

        int id; /// Purchase ID
        int cityID; /// City ID
        int foodID; /// Food ID
        int quantity; /// Purchase quantity 
        int tripID; /// Trip ID

    public:

/// @brief Constructor & Destructor Declarations 
    Purchase();
    Purchase(int id, int cityID, int foodID, int quantity, int tripID);
    ~Purchase();

/// @brief Get Function Declarations    
    int getID();
    int getCityID();
    int getFoodID();
    int getQuantity();
    int getTripID();
  
/// @brief Set Function Declarations
    void setID(int id);
    void setCityID(int cityID);
    void setFoodID(int foodID);
    void setQuantity(int quantity);
    void setTripID(int tripID);

    };
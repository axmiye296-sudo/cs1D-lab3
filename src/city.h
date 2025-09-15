/**
 * @file city.cpp
 * @brief  City entity class
 * @author CS1D Lab 3 Team
 * @date 2025
 * 
 * File contains the implementation of the City class
 */

#ifndef CITY_H
#define CITY_H

/// @class City

class City {
    private:
        int cityId;             // city id
        std::string cityName;   // city name
        
    public:
        /// @brief Default Constructor
        City() : cityId(0), cityName("City_Name") {}

        /// @brief Parameterized Constructor
        City(const int& id, const std::string& name) : cityId(id), cityName(name) {}

        /// @brief Getter Functions
        int getCityId() const { return cityId; }
        std::string getCityName() const { return cityName;}

        /// @brief Setter Functions
        void setCityId(const int id) { cityId = id; }
        void setCityName(const std::string& name) { cityName = name; }

} // end class City

#endif
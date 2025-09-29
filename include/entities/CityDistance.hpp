#ifndef CITY_DISTANCE_HPP
#define CITY_DISTANCE_HPP

#include "header.hpp"

//Forward declaration
class CityDistanceRepository;

class CityDistance {
    private:
        int id;             //PK
        int distance;
        int toCityId;     //FK
        int fromCityId;   //FK
    public:
        CityDistance();
        CityDistance(int f, int t, int d);
        int getId() const;
        int getDistance() const;
        int getToCityId() const;
        int getFromCityId() const;

        //Avoid setters for ID
        void setDistance(int distance);

        //Helper functions
        bool isValid() const;
        std::string toString() const;
        bool equals(const CityDistance& other) const;

        //Other helper functionsa

    
};

#endif
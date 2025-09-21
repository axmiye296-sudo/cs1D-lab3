//   from_city_id INTEGER REFERENCES cities(id) ON DELETE CASCADE,
//     to_city_id INTEGER REFERENCES cities(id) ON DELETE CASCADE,
//     distance NUMERIC(10,2) NOT NULL CHECK (dist


#ifndef CITYDISTANCE_HPP
#define CITYDISTANCE_HPP
#include <iostream>
#include <string>
#include "V.hpp"

class CityDistance
{
    private:
        int from_city_id;
        int to_city_id;
        int distance;
    
        public:
        CityDistance();
        CityDistance(std::string name, int id, std::string role);

        //Getters
        int getToId() const;
        int getFromId() const;
        int getDistance() const;

        //Setters
        void setToId(int i); 
        void setFromId(int i); 
        void setDistanceId(int i);

        //Validation
        //Utility Methods
};

#endif
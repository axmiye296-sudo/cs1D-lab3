#ifndef TRIP_HPP
#define TRIP_HPP

#include "header.hpp"

class Trip {
private:
    int id;
    int start_city_id;
    std::string trip_type;
    int total_distance;

public:
    // Constructors
    Trip();
    Trip(int id, int start_city_id, std::string trip_type, int total_distance);
    Trip(int start_city_id, std::string trip_type, int total_distance);

    // Getters
    int getId() const;
    int getStartCityId() const;
    int getTripType() const;
    int getTotalDistance() const;

    // Validation
    bool isValid() const;

    // Utility methods
    std::string toString() const;
    bool equals(const Trip& other) const;
};

#endif
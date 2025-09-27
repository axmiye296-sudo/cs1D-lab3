
#include "../../include/entities/trip.hpp"

    // Constructors
Trip::Trip() {}

Trip::Trip(int id, int start_city_id, std::string trip_type, double total_distance) :
    id(id), start_city_id(start_city_id), trip_type(trip_type),
     total_distance(total_distance) {}

Trip::Trip(int start_city_id, std::string trip_type, double total_distance) :
    start_city_id(start_city_id), trip_type(trip_type),
     total_distance(total_distance) {}

// Getters
int Trip::getId() const
    {
        return id;
    }
int Trip::getStartCityId() const
    {
        return start_city_id;
    }
std::string Trip::getTripType() const
    {
        return trip_type;
    }
double Trip::getTotalDistance() const
    {
        return total_distance;
    }


// Setters
void Trip::setId(int id)
    {
        this->id = id;
    }
void Trip::setStartCityId(int start_city_id)
    {
        this->start_city_id = start_city_id;
    }
void Trip::setTripType(std::string trip_type)
    {
        this->trip_type = trip_type;
    }
void Trip::setTotalDistance(double total_distance)
    {
        this->total_distance = total_distance;
    }


// Validation
bool Trip::isValid() const
    {
        return (id > 0 && start_city_id > 0 && total_distance > 0);
    }


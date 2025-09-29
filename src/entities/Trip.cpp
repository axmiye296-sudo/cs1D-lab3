#include "../../include/entities/Trip.hpp"
#include "../../include/entities/TripCity.hpp"

//Constructors
Trip::Trip() : id(0), startCityId(0), tripType(""), totalDistance(0), tripList() { }
Trip::Trip(int i, int s, std::string t, int d, V<TripCity> l) 
{
    id = i;
    startCityId = s;
    tripType = t;
    totalDistance = d;
    tripList = l;
}

//Getters
int Trip::getId() const { return id; }
int Trip::getStartCityId() const { return startCityId; }
std::string Trip::getTripType() const { return tripType; }
int Trip::getTotalDistance() const { return totalDistance; }
V<TripCity> Trip::getTripList() const { return tripList; }
int Trip::getTripSize() const 
{
    if (tripType == "fixed")
    {
        return 11;
    }
    else
    {
        return 13;
    }
}

//Setters
void Trip::setId(int i) { id = i; }
void Trip::setStartCityId(int s) { startCityId = s; }
void Trip::setTripType(std::string t) { tripType = t; }
void Trip::setTotalDistance(int d) { totalDistance = d; }





bool Trip::hasCity(int cityId) const 
{
    for (const auto& tripCity : tripList) {
        if (tripCity.getCityId() == cityId) {
            return true;
        }
    }
    return false;
}

void Trip::addTC(Trip& trip, int startCityId)
{
    int visitOrder = tripList.size() + 1;
    TripCity newTripCity(0, id, startCityId, visitOrder);
    tripList.push_back(newTripCity);
}
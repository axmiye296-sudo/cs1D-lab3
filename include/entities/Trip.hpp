#ifndef TRIP_HPP
#define TRIP_HPP

#include "../header.hpp"
#include "./TripCity.hpp"

class Trip {
private:
    int id;
    int startCityId;
    std::string tripType;
    int totalDistance;
    V<TripCity> tripList;

public:
    // Constructors
    Trip();
    Trip(int id, int start_city_id, std::string trip_type, int total_distance);
    Trip(int i, int s, std::string t, int d, V<TripCity> l); 

    // Getters
    int getId() const;
    int getStartCityId() const;
    std::string getTripType() const;
    int getTripSize() const;
    int getTotalDistance() const;
    int getNumCities() const;
    V<TripCity> getTripList() const; //const isn't allowed ig

    // Setters
    void setId(int id);
    void setStartCityId(int start_city_id);
    void setTripType(std::string trip_type);
    void setTotalDistance(int total_distance);

    // Validation
    bool isValid() const;

    // Utility methods
    std::string toString() const;
    bool equals(const Trip& other) const;
	
    //Others
    int getMaxTripSize() const;
    bool hasCity(int cityId) const;
    void addTC(Trip& trip, int startCityId);

};

#endif
#ifndef TRIP_CITY_HPP
#define TRIP_CITY_HPP

#include "header.hpp"
#include <string>
#include <memory>

// Forward declaration
class TripCityRepository;

class TripCity {
private:
    int id;
    int tripId;
    int cityId;
    int visitOrder;

public:
    // Constructors
    TripCity();
    TripCity(int id, int tripId, int cityId, int visitOrder);
    TripCity(int tripId, int cityId, int visitOrder);

    // Getters
    int getId() const;
    int getTripId() const;
    int getCityId() const;
    int getVisitOrder() const;

    // Setters
    void setId(int id);
    void setTripId(int tripId);
    void setCityId(int cityId);
    void setVisitOrder(int visitOrder);

    // Validation
    bool isValid() const;

     // Utility methods
    std::string toString() const;
    bool equals(const TripCity& other) const;
};

#endif
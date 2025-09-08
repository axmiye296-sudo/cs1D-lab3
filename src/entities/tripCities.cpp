#include "../../include/entities/tripCities.hpp"

// Constructors
TripCity::TripCity() : id(0), tripId(0), cityId(0), visitOrder(0) {}

TripCity::TripCity(int id, int tripId, int cityId, int visitOrder) 
    : id(id), tripId(tripId), cityId(cityId), visitOrder(visitOrder) {}

TripCity::TripCity(int tripId, int cityId, int visitOrder) 
    : id(0), tripId(tripId), cityId(cityId), visitOrder(visitOrder) {}

// Getters and setters
int TripCity::getId() const { return id; }
int TripCity::getTripId() const { return tripId; }
int TripCity::getCityId() const { return cityId; }
int TripCity::getVisitOrder() const { return visitOrder; }

void TripCity::setId(int id) { this->id = id; }
void TripCity::setTripId(int tripId) { this->tripId = tripId; }
void TripCity::setCityId(int cityId) { this->cityId = cityId; }
void TripCity::setVisitOrder(int visitOrder) { this->visitOrder = visitOrder; }

// Validation
bool TripCity::isValid() const {
    return tripId > 0 && cityId > 0 && visitOrder > 0;
}

// Utility methods
std::string TripCity::toString() const {
    return "TripCity{id=" + std::to_string(id) +
           ", tripId=" + std::to_string(tripId) +
           ", cityId=" + std::to_string(cityId) +
           ", visitOrder=" + std::to_string(visitOrder) + "}";
}

bool TripCity::equals(const TripCity& other) const {
    return id == other.id && tripId == other.tripId &&
           cityId == other.cityId && visitOrder == other.visitOrder;
}
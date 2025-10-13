#include "../../include/entities/CityDistance.hpp"

CityDistance::CityDistance() : fromCityId(0), toCityId(0), distance(0) {}

CityDistance::CityDistance(int fromCityId, int toCityId, int distance)
    : fromCityId(fromCityId), toCityId(toCityId), distance(distance) {}

int CityDistance::getFromCityId() const { return fromCityId; }
int CityDistance::getToCityId() const { return toCityId; }
int CityDistance::getDistance() const { return distance; }

void CityDistance::setFromCityId(int fromCityId) { this->fromCityId = fromCityId; }
void CityDistance::setToCityId(int toCityId) { this->toCityId = toCityId; }
void CityDistance::setDistance(int distance) { this->distance = distance; }




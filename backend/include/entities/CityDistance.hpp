#ifndef CITY_DISTANCE_HPP
#define CITY_DISTANCE_HPP

class CityDistance {
private:
    int fromCityId;
    int toCityId;
    int distance;

public:
    CityDistance();
    CityDistance(int fromCityId, int toCityId, int distance);

    // Getters
    int getFromCityId() const;
    int getToCityId() const;
    int getDistance() const;

    // Setters
    void setFromCityId(int fromCityId);
    void setToCityId(int toCityId);
    void setDistance(int distance);
};

#endif

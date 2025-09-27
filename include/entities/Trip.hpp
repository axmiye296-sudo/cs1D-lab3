#ifndef TRIP_HPP
#define TRIP_HPP

#include "../header.hpp"

class Trip {
    private:
        int id;
        int start_city_id;
        std::string trip_type;
        double total_distance;
        //int numCities;

    public:
        // Constructors
        Trip();
        Trip(int id, int start_city_id, std::string trip_type, double total_distance);
        Trip(int start_city_id, std::string trip_type, double total_distance);

        // Getters
        int getId() const;
        int getStartCityId() const;
        std::string getTripType() const;
        double getTotalDistance() const;
        //int getNumCities() const;

        // Setters
        void setId(int id);
        void setStartCityId(int start_city_id);
        void setTripType(std::string trip_type);
        void setTotalDistance(double total_distance);
        //void setNumCities(int numCities);

        // Validation
        bool isValid() const;

        // Utility methods
        std::string toString() const;
        bool equals(const Trip& other) const;

};

#endif
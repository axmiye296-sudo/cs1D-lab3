#ifndef CITY_SERVICE_HPP
#define CITY_SERVICE_HPP

#include "../header.hpp"
#include "../entities/City.hpp"

class CityRepository;

class CityService {
    private:
        CityRepository& cityRepo; //we need this to get city data

    public:
        CityService(CityRepository& cityRepo);    //takes city repository and stores it for later use

        V<City> getAllCities();
        void displayAllCities();

    private:
        void displayCity(const City& city);    //to display one city

};

#endif
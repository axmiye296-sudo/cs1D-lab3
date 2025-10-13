#ifndef TRIP_ROUTES_HPP
#define TRIP_ROUTES_HPP

#include "crow/crow_all.h"
#include "../services/TripService.hpp"
#include "../services/CityService.hpp"
#include "../services/tripCityService.hpp"

void registerTripRoutes(crow::SimpleApp& app, TripService& tripService, CityService& cityService, TripCityService& tripCityService);

#endif
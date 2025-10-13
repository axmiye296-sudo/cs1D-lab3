#ifndef CITY_ROUTES_HPP
#define CITY_ROUTES_HPP

#include <crow.h>
#include "../services/CityService.hpp"
#include "../services/FoodService.hpp"
#include "../repositories/CityDistanceRepository.hpp"

void registerCityRoutes(crow::SimpleApp& app, CityService& cityService, FoodService& foodService, CityDistanceRepository& cityDistanceRepo);

#endif

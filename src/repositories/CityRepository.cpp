#include "../../include/repositories/CityRepository.hpp"
#include <iostream>

CityRepository::CityRepository(DatabaseManager& database) : db(database) {}


std::string CityRepository::getCityNameById(int cityId) {
    std::string query = "SELECT name FROM cities WHERE id = " + std::to_string(cityId) + ";";
    auto result = db.executeSelect(query);
    if (!result.empty() && !result[0].empty()) {
        return result[0][0];
    }
    return "[Unknown]";
}
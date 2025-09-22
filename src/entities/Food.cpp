#include "../../include/entities/Food.hpp"


Food::Food() : id(0), name(""), cityId(0), price(0.0) {
}

Food::Food(int id, const std::string& name, int cityId, double price)
    : id(id), name(name), cityId(cityId), price(price) {
}

int Food::getId() const {
    return id;
}

std::string Food::getName() const {
    return name;
}

int Food::getCityId() const {
    return cityId;
}

double Food::getPrice() const {
    return price;
}

void Food::setId(int id) {
    this->id = id;
}

void Food::setName(const std::string& name) {
    this->name = name;
}

void Food::setCityId(int cityId) {
    this->cityId = cityId;
}

void Food::setPrice(double price) {
    this->price = price;
}

void Food::print() const {
    std::cout << "  - " << name << " (€" << std::fixed << std::setprecision(2) << price << ")" << std::endl;
    // Example output: "  - Croissant (€2.50)"
}
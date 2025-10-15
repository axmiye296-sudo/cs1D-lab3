#include "../../include/entities/City.hpp"

City::City() : id(0), name("") {
}

City::City(int id, const std::string& name) : id(id), name(name) {
}

int City::getId() const {
    return id;
}

std::string City::getName() const {
    return name;
}

void City::setId(int id) {
    this->id = id;
}

void City::setName(const std::string& name) {
    this->name = name;
}


void City::print() const {
    std::cout << "ID: " << id << ", Name: " << name << std::endl;
    // Example output: "ID: 1, Name: Paris"
}
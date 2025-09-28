/**
 * ENTITY LAYER IMPLEMENTATION: User class
 */

#include "../include/User.hpp"
#include <sstream>

// Default constructor
User::User() : id(0), name(""), role("") {}

// Full constructor
User::User(std::string name, int id, std::string role)
    : id(id), name(std::move(name)), role(std::move(role)) {}

// Getters
int User::getId() const {
    return id;
}

std::string User::getName() const {
    return name;
}

std::string User::getRole() const {
    return role;
}

// Setters
void User::setId(int i) {
    id = i;
}

void User::setName(std::string s) {
    name = std::move(s);
}

void User::setRole(std::string r) {
    role = std::move(r);
}

// Validation
bool User::isValid() const {
    return (id > 0 && !name.empty() && !role.empty());
}

// Utility Methods
std::string User::toString() const {
    std::ostringstream oss;
    oss << "User[ID=" << id 
        << ", Name=" << name 
        << ", Role=" << role << "]";
    return oss.str();
}

bool User::equals(const User& other) const {
    return (id == other.id &&
            name == other.name &&
            role == other.role);
}

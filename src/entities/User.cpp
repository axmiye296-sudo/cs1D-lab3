#include "../../include/entities/User.hpp"


User::User() {}

User::User(std::string n, int i, std::string r) {
    name = n;
    id = i;
    role = r;
}

int User::getId() const
{
    return id;
}

std::string User::getName() const
{
    return name;
}

std::string User::getRole() const
{
    return role;
}

void User::setId(int i)
{
    id = i;
}

void User::setName(std::string n)
{
    name = n;
}

void User::setRole(std::string r)
{
    role = r;
}
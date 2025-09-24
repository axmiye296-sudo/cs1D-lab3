// Users.h

#pragma once

#include "header.hpp"


class Users
{
private:
    int id;
    std::string name;
    std::string password;

public:

    Users();
    ~Users();

    int getID() const;
    void setID(const int& ID);

    std::string getName() const;
    void setName(const std::string& name);

    std::string getPassword() const;
    void setPassword(const std::string& password);

};
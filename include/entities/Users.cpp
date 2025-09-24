// Users.cpp

#include "Users.h"

    Users::Users(): name("0"), password("0") {}

    Users::~Users() {}

    int Users::getID() const
    {
        return id;
    }

    void Users::setID(int id)
    {
        this->id = id;
    }

       std::string Users::getName() const
       {
        return name;
       }

    void Users::setName(const std::string& name)
    {
        this->name = name;
    }

    std::string Users::getPassword() const
    {
        return password;
    }

    void Users::setPassword(const std::string& password) 
    {
        this->password = password;
    }
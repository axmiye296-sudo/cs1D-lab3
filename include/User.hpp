#ifndef USER_HPP
#define USER_HPP
#include <iostream>
#include <string>
#include "V.hpp"

class User
{
    private:
        std::string name;
        int id;
        std::string role;

    public:
        User();
        User(std::string name, int id, std::string role);

        //Getters
        int getId() const;
        std::string getName() const;
        std::string getRole() const;

        //Setters
        void setId(int i); 
        void setName(std::string s);
        void setRole(std::string r);

        //Validation
        //Utility Methods
};


#endif
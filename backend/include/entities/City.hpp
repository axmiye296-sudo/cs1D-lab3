#ifndef CITY_HPP
#define CITY_HPP

#include "../header.hpp"

class City {
  private:
    int id;
    std::string name;

  public:
    City();
    City(int id, const std::string& name);

    //getters
    int getId() const;                         // Returns the city's ID number
    std::string getName() const;

    //setters
    void setId(int id);
    void setName(const std::string& name);

    void print() const;
};


#endif
#ifndef HEADER_HPP
#define HEADER_HPP
#include <iostream>
#include <string>
#include "V.hpp"
#include <memory>
#include <vector>
#include <iomanip>

class DatabaseManager;

void displayMainMenu();
int handleMenuChoice(DatabaseManager& database);
void showCityAndFood(DatabaseManager& database);

#endif
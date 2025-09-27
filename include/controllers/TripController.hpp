#ifndef TRIP_CONTROLLER_HPP
#define TRIP_CONTROLLER_HPP

#include "../databaseManager.hpp"
#include "../services/TripService.hpp"

void showTripController(DatabaseManager& database);
void displayTripMenu();
bool handleTripChoice(int choice, TripService& tripService, DatabaseManager& database);
void waitForUser();

#endif
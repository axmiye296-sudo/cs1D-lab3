#include "../include/services/TripService.hpp"

TripService::TripService(TripRepository& repo) : tripRepo(repo) {}
TripService::~TripService() {}

bool TripService::createTrip(int startCityId, const std::string& type, int distance) {
    Trip trip(startCityId, type, distance);
    return tripRepo.save(trip);
}

bool TripService::updateTrip(Trip& trip) {
    return tripRepo.save(trip);
}

bool TripService::deleteTrip(int id) {
    return tripRepo.remove(id);
}

Trip TripService::getTrip(int id) {
    return tripRepo.findById(id);
}

V<Trip> TripService::listTrips() {
    return tripRepo.findAll();
}

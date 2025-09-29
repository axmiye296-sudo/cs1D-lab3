#ifndef USER_REPOSITORY_HPP
#define USER_REPOSITORY_HPP

#include "../header.hpp"
#include "../entities/User.hpp"

class DatabaseManager;  // forward declaration

class UserRepository {
 private:
    DatabaseManager& database;  // reference to the DB connection
    User mapRowToEntity(const std::vector<std::string>& row);

 public:
    // Constructor takes a reference to the DB connection
    UserRepository(DatabaseManager& db);

    // Returns all users in the database
    V<User> findAll();

    // You can add more methods as needed, e.g.:
    // User findById(int id);
    // void save(const User& user);
    // void update(const User& user);
    // void remove(int id);
};

#endif
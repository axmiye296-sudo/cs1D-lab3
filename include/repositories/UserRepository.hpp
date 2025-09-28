#ifndef USER_REPOSITORY_HPP
#define USER_REPOSITORY_HPP

#include "../header.hpp"
#include "../databaseManager.hpp"
#include "../entities/User.hpp"

/**
 * @class UserRepository
 * @brief Repository pattern implementation for User data access
 * 
 * This class handles all database operations for User entities,
 * providing a clean interface between the service layer and database layer.
 * Implements the Repository pattern for better separation of concerns.
 */
class UserRepository {
private:
    DatabaseManager& db; ///< Reference to the database manager

public:
    /**
     * @brief Constructor
     * @param database Reference to the database manager
     */
    UserRepository(DatabaseManager& database);

    // CRUD operations
    /**
     * @brief Save a User entity to the database
     * @param user The User object to save
     * @return true if successful, false otherwise
     * @note If ID is 0, performs INSERT; otherwise performs UPDATE
     */
    bool save(User& user);

    /**
     * @brief Load a User entity from the database by ID
     * @param id The database ID to load
     * @param user Reference to User object to populate
     * @return true if found and loaded, false otherwise
     */
    bool load(int id, User& user);

    /**
     * @brief Remove a User entity from the database
     * @param id The database ID to remove
     * @return true if successful, false otherwise
     */
    bool remove(int id);

    /**
     * @brief Get all User entities from the database
     * @return Vector containing all User objects
     */
    V<User> findAll();

    // User-specific queries
    /**
     * @brief Find a user by name
     * @param name The user name to search for
     * @return Vector of User objects with matching names
     */
    V<User> findByName(const std::string& name);

    /**
     * @brief Find a user by role
     * @param role The role to search for
     * @return Vector of User objects with matching role
     */
    V<User> findByRole(const std::string& role);

private:
    // Helper methods
    /**
     * @brief Convert database row to User entity
     * @param row Database row as vector of strings
     * @return User object created from the row
     */
    User mapRowToEntity(const std::vector<std::string>& row);

    /**
     * @brief Build INSERT SQL query for User
     * @param user The User object to insert
     * @return SQL INSERT query string
     */
    std::string buildInsertQuery(const User& user);

    /**
     * @brief Build UPDATE SQL query for User
     * @param user The User object to update
     * @return SQL UPDATE query string
     */
    std::string buildUpdateQuery(const User& user);

    /**
     * @brief Build DELETE SQL query for User
     * @param id The ID to delete
     * @return SQL DELETE query string
     */
    std::string buildDeleteQuery(int id);

    /**
     * @brief Build SELECT SQL query for User by ID
     * @param id The ID to select
     * @return SQL SELECT query string
     */
    std::string buildSelectQuery(int id);

    /**
     * @brief Build SELECT SQL query for all User records
     * @return SQL SELECT query string
     */
    std::string buildSelectAllQuery();
};

#endif // USER_REPOSITORY_HPP

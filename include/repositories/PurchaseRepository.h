#pragma once

#include "header.hpp"
#include "../entities/purchase.h"
#include "../databaseManager.hpp"

class PurchaseRepository
{
private:
    //std::vector<Purchase> purchases;
    databaseManager& db; ///< Reference to the database manager

public:
    PurchaseRepository(databaseManager& database);

    /// @brief Save a purchase to the database
    /// @param purchase 
    /// @return true if successful, false otherwise
    bool save(Purchase& purchase);

    /// @brief Load a purchase from the database
    /// @param id The ID of the purchase to load
    /// @param purchase The purchase object to populate
    /// @return true if successful, false otherwise
    bool load(int id, Purchase& purchase);

    bool remove(int id);

    V<Purchase> findAll();

    V<Purchase> findByCity(int cityID);

    V<Purchase> findByTrip(int tripID);

    V<Purchase> findByFood(int foodID);

    bool saveAll(const V<Purchase>& purchases);

    bool removeByPurchase(int id);


private:

/// Helper methods for database operations

    Purchase mapRowToEntity(const V<std::string>& row);

    std::string buildInsertQuery(const Purchase& purchase);

    std::string buildUpdateQuery(const Purchase& purchase);

    std::string buildDeleteQuery(int id);

    std::string buildSelectQuery(int id);

    std::string buildSelectAllQuery();

    std::string buildSelectByTripQuery(int tripID);

};

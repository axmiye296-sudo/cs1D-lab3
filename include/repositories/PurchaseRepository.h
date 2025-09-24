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
    void addPurchase(const Purchase& purchase);
    void removePurchase(int id);
    Purchase getPurchase(int id) const;
    std::vector<Purchase> getAllPurchases() const;
};


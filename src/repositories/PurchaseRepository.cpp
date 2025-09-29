 /// @file PurchaseRepository.cpp

 #include "PurchaseRepository.h"
 
 PurchaseRepository::PurchaseRepository(databaseManager& database) : db(database) {}

    /// @brief Save a purchase to the database
    /// @param purchase 
    /// @return true if successful, false otherwise
    bool  PurchaseRepository::save(Purchase& purchase)
    {
        std::string query;
        if(purchase.getID() == 0)
        {
            query = buildInsertQuery(purchase);
        }
        else
        {
            query = buildUpdateQuery(purchase);
        }
        return db.executeQuery(query);
    }

    /// @brief Load a purchase from the database
    /// @param id The ID of the purchase to load
    /// @param purchase The purchase object to populate
    /// @return true if successful, false otherwise
    bool  PurchaseRepository::load(int id, Purchase& purchase)
    {
        std::string query = buildSelectQuery(id);
        auto dbResult = db.executeSelect(query);
        
        if (!dbResult.empty() && dbResult[0].size() >= 5 )
        {
            purchase = mapRowToEntity(dbResult[0]);
            return true;
        }
        return false;
    }

    bool  PurchaseRepository::remove(int id)
    {
        std::string query = buildDeleteQuery(id);
        return db.executeQuery(query);
    }

    V<Purchase>  PurchaseRepository::findAll()
    {
        V<Purchase> result;
        std::string query = buildSelectAllQuery();
        auto dbResult = db.executeSelect(query);

        if(!dbResult.empty())
            for(const auto& row : dbResult)
                if(row.size() >= 4)  
                {
                    Purchase purchase = mapRowToEntity(row)
                    result.push_back(purchase);
                }
                return result;
    }

    V<Purchase>  PurchaseRepository::findByCity(int cityID)
    {
        V<Purchase> result;
        std::string query = "SELECT id, trip_id, food_id, city_id, quantity FROM purchases WHERE city_id = "
             + std::to_string(cityID) + " ORDER BY id;";
    }

    V<Purchase>  PurchaseRepository::findByTrip(int tripID);

    V<Purchase>  PurchaseRepository::findByFood(int foodID);

    bool  PurchaseRepository::saveAll(const V<Purchase>& purchases);

    bool  PurchaseRepository::removeByPurchase(int id);

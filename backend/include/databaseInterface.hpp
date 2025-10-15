/**
 * Database Interface
 * Common interface for different database implementations
 */

#ifndef DATABASE_INTERFACE_HPP
#define DATABASE_INTERFACE_HPP

#include "header.hpp"

class DatabaseInterface {
public:
    virtual ~DatabaseInterface() = default;
    
    // Connection management
    virtual bool connect() = 0;
    virtual void disconnect() = 0;
    virtual bool isConnected() const = 0;
    
    // Generic query execution
    virtual bool executeQuery(const std::string& query) = 0;
    virtual V<std::vector<std::string>> executeSelect(const std::string& query) = 0;
    virtual int executeInsert(const std::string& query) = 0;
    virtual bool executeUpdate(const std::string& query) = 0;
    virtual bool executeDelete(const std::string& query) = 0;
    
    // Transaction management
    virtual bool beginTransaction() = 0;
    virtual bool commitTransaction() = 0;
    virtual bool rollbackTransaction() = 0;
};

#endif

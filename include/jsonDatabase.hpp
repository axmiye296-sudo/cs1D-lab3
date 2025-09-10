/**
 * JSON Database Manager
 * Simple mock database using JSON files instead of PostgreSQL
 * Provides CRUD operations for development and testing
 */

#ifndef JSON_DATABASE_HPP
#define JSON_DATABASE_HPP

#include "header.hpp"
#include <fstream>
#include <sstream>
#include <map>
#include <regex>

class JsonDatabase {
private:
    std::string dataDirectory;
    std::map<std::string, V<std::map<std::string, std::string>>> tables;
    std::map<std::string, int> nextIds;

    // Helper methods
    std::map<std::string, std::string> parseJsonObject(const std::string& jsonStr);
    std::string mapToJson(const std::map<std::string, std::string>& data);

public:
    JsonDatabase(const std::string& dir = "./mock_data");
    
    // Load/Save data
    bool loadTable(const std::string& tableName);
    bool saveTable(const std::string& tableName);
    
    // Raw CRUD operations (no SQL)
    V<std::map<std::string, std::string>> select(const std::string& tableName);
    V<std::map<std::string, std::string>> selectWhere(const std::string& tableName, 
                                                      const std::string& column, 
                                                      const std::string& value);
    int insert(const std::string& tableName, const std::map<std::string, std::string>& data);
    bool update(const std::string& tableName, int id, const std::map<std::string, std::string>& data);
    bool remove(const std::string& tableName, int id);
    
    // Utility
    void printTable(const std::string& tableName);
    int getNextId(const std::string& tableName);
};

#endif

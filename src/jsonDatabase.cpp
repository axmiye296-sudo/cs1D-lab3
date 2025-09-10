/**
 * JSON Database Implementation
 * Handles loading/saving JSON files and basic CRUD operations
 * No SQL required - uses direct C++ function calls
 */

#include "../include/jsonDatabase.hpp"
#include <iostream>
#include <filesystem>

JsonDatabase::JsonDatabase(const std::string& dir) : dataDirectory(dir) {
    // Initialize table names
    std::vector<std::string> tableNames = {
        "cities", "foods", "city_distances", "trips", 
        "trip_cities", "purchases", "users"
    };
    
    for (const auto& tableName : tableNames) {
        nextIds[tableName] = 1;
        loadTable(tableName);
    }
}

bool JsonDatabase::loadTable(const std::string& tableName) {
    std::string filename = dataDirectory + "/" + tableName + ".json";
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cout << "Table " << tableName << " not found, creating empty table" << std::endl;
        tables[tableName] = V<std::map<std::string, std::string>>();
        return false;
    }
    
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    file.close();
    
    // Simple JSON parsing
    tables[tableName] = V<std::map<std::string, std::string>>();
    
    // Find the highest ID
    int maxId = 0;
    std::string idPattern = "\"id\"\\s*:\\s*\"(\\d+)\"";
    std::regex idRegex(idPattern);
    std::sregex_iterator iter(content.begin(), content.end(), idRegex);
    std::sregex_iterator end;
    
    for (; iter != end; ++iter) {
        int id = std::stoi((*iter)[1].str());
        maxId = std::max(maxId, id);
    }
    
    nextIds[tableName] = maxId + 1;
    
    // Parse JSON objects
    std::regex objectRegex(R"(\{[^}]*\})");
    std::sregex_iterator objIter(content.begin(), content.end(), objectRegex);
    
    for (; objIter != end; ++objIter) {
        std::string objStr = (*objIter).str();
        std::map<std::string, std::string> obj = parseJsonObject(objStr);
        if (!obj.empty()) {
            tables[tableName].push_back(obj);
        }
    }
    
    std::cout << "Loaded " << tables[tableName].size() << " rows from " << tableName << std::endl;
    return true;
}

bool JsonDatabase::saveTable(const std::string& tableName) {
    std::string filename = dataDirectory + "/" + tableName + ".json";
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Failed to save table " << tableName << std::endl;
        return false;
    }
    
    file << "[\n";
    for (size_t i = 0; i < tables[tableName].size(); ++i) {
        file << "  " << mapToJson(tables[tableName][i]);
        if (i < tables[tableName].size() - 1) {
            file << ",";
        }
        file << "\n";
    }
    file << "]\n";
    file.close();
    
    return true;
}

V<std::map<std::string, std::string>> JsonDatabase::select(const std::string& tableName) {
    if (tables.find(tableName) == tables.end()) {
        std::cerr << "Table " << tableName << " not found" << std::endl;
        return V<std::map<std::string, std::string>>();
    }
    return tables[tableName];
}

V<std::map<std::string, std::string>> JsonDatabase::selectWhere(const std::string& tableName, 
                                                               const std::string& column, 
                                                               const std::string& value) {
    V<std::map<std::string, std::string>> result;
    
    if (tables.find(tableName) == tables.end()) {
        return result;
    }
    
    for (const auto& row : tables[tableName]) {
        if (row.find(column) != row.end() && row.at(column) == value) {
            result.push_back(row);
        }
    }
    
    return result;
}

int JsonDatabase::insert(const std::string& tableName, const std::map<std::string, std::string>& data) {
    if (tables.find(tableName) == tables.end()) {
        std::cerr << "Table " << tableName << " not found" << std::endl;
        return -1;
    }
    
    std::map<std::string, std::string> newRow = data;
    int newId = getNextId(tableName);
    newRow["id"] = std::to_string(newId);
    
    tables[tableName].push_back(newRow);
    saveTable(tableName);
    
    std::cout << "Inserted new record with ID " << newId << " into " << tableName << std::endl;
    return newId;
}

bool JsonDatabase::update(const std::string& tableName, int id, const std::map<std::string, std::string>& data) {
    if (tables.find(tableName) == tables.end()) {
        return false;
    }
    
    for (auto& row : tables[tableName]) {
        if (row.find("id") != row.end() && std::stoi(row["id"]) == id) {
            for (const auto& field : data) {
                row[field.first] = field.second;
            }
            saveTable(tableName);
            std::cout << "Updated record with ID " << id << " in " << tableName << std::endl;
            return true;
        }
    }
    
    return false;
}

bool JsonDatabase::remove(const std::string& tableName, int id) {
    if (tables.find(tableName) == tables.end()) {
        return false;
    }
    
    // Find and remove the item
    for (size_t i = 0; i < tables[tableName].size(); i++) {
        if (tables[tableName][i].find("id") != tables[tableName][i].end() && 
            std::stoi(tables[tableName][i]["id"]) == id) {
            
            // Create new V without the item to remove
            V<std::map<std::string, std::string>> newTable;
            for (size_t j = 0; j < tables[tableName].size(); j++) {
                if (j != i) {
                    newTable.push_back(tables[tableName][j]);
                }
            }
            tables[tableName] = newTable;
            saveTable(tableName);
            std::cout << "Removed record with ID " << id << " from " << tableName << std::endl;
            return true;
        }
    }
    
    return false;
}

void JsonDatabase::printTable(const std::string& tableName) {
    if (tables.find(tableName) == tables.end()) {
        std::cout << "Table " << tableName << " not found" << std::endl;
        return;
    }
    
    std::cout << "\n=== " << tableName << " ===" << std::endl;
    for (const auto& row : tables[tableName]) {
        for (const auto& field : row) {
            std::cout << field.first << ": " << field.second << " | ";
        }
        std::cout << std::endl;
    }
    std::cout << "Total rows: " << tables[tableName].size() << std::endl;
}

int JsonDatabase::getNextId(const std::string& tableName) {
    return nextIds[tableName]++;
}

std::map<std::string, std::string> JsonDatabase::parseJsonObject(const std::string& jsonStr) {
    std::map<std::string, std::string> result;
    
    // Simple JSON parsing - extract key-value pairs
    std::regex fieldRegex("\"([^\"]+)\"\\s*:\\s*\"([^\"]+)\"");
    std::sregex_iterator iter(jsonStr.begin(), jsonStr.end(), fieldRegex);
    std::sregex_iterator end;
    
    for (; iter != end; ++iter) {
        result[(*iter)[1].str()] = (*iter)[2].str();
    }
    
    return result;
}

std::string JsonDatabase::mapToJson(const std::map<std::string, std::string>& data) {
    std::stringstream json;
    json << "{\n";
    
    size_t count = 0;
    for (const auto& field : data) {
        json << "    \"" << field.first << "\": \"" << field.second << "\"";
        if (++count < data.size()) {
            json << ",";
        }
        json << "\n";
    }
    
    json << "  }";
    return json.str();
}

/**
 * @file adminRoutes.cpp
 * @brief Implementation of admin-related API routes
 */

#include "crow/crow_all.h"
#include "../../include/entities/Admin.hpp"
#include "../../include/services/AdminService.hpp"
#include "../../include/routes/adminRoutes.hpp"

/**
 * @brief Macro for admin authentication check
 * @param adminService Reference to AdminService instance
 * @param res Reference to Crow response object
 * 
 * Checks if an admin is currently logged in. If not, returns a 403 Unauthorized response.
 * This macro is used throughout admin routes to ensure proper authentication.
 */
#define ADMIN_AUTH_CHECK(adminService, res) \
    if (!adminService.isAdminLoggedIn()) { \
        crow::json::wvalue error; \
        error["error"] = "Unauthorized: Admin login required"; \
        res.code = 403; \
        res.write(error.dump()); \
        res.end(); \
        return; \
    }

/**
 * @brief Register admin-related API routes
 * @param app Reference to Crow SimpleApp instance
 * @param adminService Reference to AdminService for administrative operations
 * 
 * Registers all admin-related API endpoints including:
 * - POST /api/admin/login - Admin authentication
 * - POST /api/admin/logout - Admin logout
 * - City management endpoints (add, update, delete, list)
 * - Food management endpoints (add, update, delete, list)
 * - File processing endpoints for data import
 */
void registerAdminRoutes(crow::SimpleApp& app, AdminService& adminService) {

    // ============================================================================
    // AUTHENTICATION ROUTES
    // ============================================================================

    /**
     * @brief POST /api/admin/login - Admin authentication
     * 
     * Authenticates an admin user with username and password.
     * Request body: {"username": "admin", "password": "password"}
     * Response: {"success": true/false, "message": "Login successful" or "Invalid credentials"}
     */
    CROW_ROUTE(app, "/api/admin/login").methods("POST"_method)
    ([&adminService](const crow::request& req, crow::response& res) {
        auto body = crow::json::load(req.body);
        if (!body || !body.has("username") || !body.has("password")) {
            crow::json::wvalue error;
            error["error"] = "Invalid JSON format or missing fields";
            res.code = 400;
            res.write(error.dump());
            res.end();
            return;
        }

        bool success = adminService.loginAdmin(body["username"].s(), body["password"].s());
        crow::json::wvalue result;
        result["success"] = success;
        result["message"] = success ? "Login successful" : "Invalid credentials";
        res.code = 200;
        res.write(result.dump());
        res.end();
    });

    /**
     * @brief POST /api/admin/logout - Admin logout
     * 
     * Logs out the currently authenticated admin user.
     * Requires admin authentication.
     * Response: {"message": "Admin logged out successfully"}
     */
    CROW_ROUTE(app, "/api/admin/logout").methods("POST"_method)
    ([&adminService](const crow::request& req, crow::response& res) {
        ADMIN_AUTH_CHECK(adminService, res);

        adminService.logoutAdmin();
        crow::json::wvalue result;
        result["message"] = "Admin logged out successfully";
        res.code = 200;
        res.write(result.dump());
        res.end();
    });

    // GET /api/admin/info
    CROW_ROUTE(app, "/api/admin/info").methods("GET"_method)
    ([&adminService](const crow::request& req, crow::response& res) {
        ADMIN_AUTH_CHECK(adminService, res);

        crow::json::wvalue info;
        info["username"] = "admin";
        info["isLoggedIn"] = true;
        res.code = 200;
        res.write(info.dump());
        res.end();
    });

    // GET /api/admin/cities
    CROW_ROUTE(app, "/api/admin/cities").methods("GET"_method)
    ([&adminService](const crow::request& req, crow::response& res) {
        ADMIN_AUTH_CHECK(adminService, res);

        auto cities = adminService.getAllCities();

        crow::json::wvalue::list cityArray;
        for (const auto& city : cities) {
            crow::json::wvalue c;
            c["id"] = city.getId();
            c["name"] = city.getName();
            cityArray.emplace_back(std::move(c));
        }

        crow::json::wvalue result;
        result["cities"] = std::move(cityArray);
        res.code = 200;
        res.write(result.dump());
        res.end();
    });

    // POST /api/admin/cities
    CROW_ROUTE(app, "/api/admin/cities").methods("POST"_method)
    ([&adminService](const crow::request& req, crow::response& res) {
        ADMIN_AUTH_CHECK(adminService, res);

        auto body = crow::json::load(req.body);
        if (!body || !body.has("name")) {
            crow::json::wvalue error;
            error["error"] = "Missing city name";
            res.code = 400;
            res.write(error.dump());
            res.end();
            return;
        }

        bool success = adminService.addNewCity(body["name"].s());
        crow::json::wvalue result;
        if (success) {
            result["message"] = "City added successfully";
            res.code = 201;
        } else {
            result["error"] = "Failed to add city";
            res.code = 500;
        }
        res.write(result.dump());
        res.end();
    });

    // PUT /api/admin/cities/<int>
    CROW_ROUTE(app, "/api/admin/cities/<int>").methods("PUT"_method, "PATCH"_method)
    ([&adminService](const crow::request& req, crow::response& res, int cityId) {
        ADMIN_AUTH_CHECK(adminService, res);

        auto body = crow::json::load(req.body);
        if (!body || !body.has("name")) {
            crow::json::wvalue error;
            error["error"] = "Missing new city name";
            res.code = 400;
            res.write(error.dump());
            res.end();
            return;
        }

        bool success = adminService.updateCityName(cityId, body["name"].s());
        crow::json::wvalue result;
        if (success) {
            result["message"] = "City updated successfully";
            res.code = 200;
        } else {
            result["error"] = "Failed to update city";
            res.code = 404;
        }
        res.write(result.dump());
        res.end();
    });

    // DELETE /api/admin/cities/<int>
    CROW_ROUTE(app, "/api/admin/cities/<int>").methods("DELETE"_method)
    ([&adminService](const crow::request& req, crow::response& res, int cityId) {
        ADMIN_AUTH_CHECK(adminService, res);

        bool success = adminService.deleteCity(cityId);
        crow::json::wvalue result;
        if (success) {
            result["message"] = "City deleted successfully";
            res.code = 200;
        } else {
            result["error"] = "Failed to delete city";
            res.code = 404;
        }
        res.write(result.dump());
        res.end();
    });

    // GET /api/admin/foods
    CROW_ROUTE(app, "/api/admin/foods").methods("GET"_method)
    ([&adminService](const crow::request& req, crow::response& res) {
        ADMIN_AUTH_CHECK(adminService, res);

        auto foods = adminService.getAllFoods();

        crow::json::wvalue::list foodArray;
        for (const auto& food : foods) {
            crow::json::wvalue f;
            f["id"] = food.getId();
            f["name"] = food.getName();
            f["price"] = food.getPrice();
            f["cityId"] = food.getCityId();
            foodArray.emplace_back(std::move(f));
        }

        crow::json::wvalue result;
        result["foods"] = std::move(foodArray);
        res.code = 200;
        res.write(result.dump());
        res.end();
    });

    // POST /api/admin/cities/<int>/foods
    CROW_ROUTE(app, "/api/admin/cities/<int>/foods").methods("POST"_method)
    ([&adminService](const crow::request& req, crow::response& res, int cityId) {
        ADMIN_AUTH_CHECK(adminService, res);

        auto body = crow::json::load(req.body);
        if (!body || !body.has("name") || !body.has("price")) {
            crow::json::wvalue error;
            error["error"] = "Missing food name or price";
            res.code = 400;
            res.write(error.dump());
            res.end();
            return;
        }

        bool success = adminService.addFoodToCity(cityId, body["name"].s(), body["price"].d());
        crow::json::wvalue result;
        if (success) {
            result["message"] = "Food added successfully";
            res.code = 201;
        } else {
            result["error"] = "Failed to add food";
            res.code = 500;
        }
        res.write(result.dump());
        res.end();
    });

    // PUT /api/admin/foods/<int>
    CROW_ROUTE(app, "/api/admin/foods/<int>").methods("PUT"_method, "PATCH"_method)
    ([&adminService](const crow::request& req, crow::response& res, int foodId) {
        ADMIN_AUTH_CHECK(adminService, res);

        auto body = crow::json::load(req.body);
        if (!body) {
            crow::json::wvalue error;
            error["error"] = "Invalid JSON";
            res.code = 400;
            res.write(error.dump());
            res.end();
            return;
        }

        bool success = true;

        if (!body.has("name") && !body.has("price")) {
            crow::json::wvalue error;
            error["error"] = "Nothing to update";
            res.code = 400;
            res.write(error.dump());
            res.end();
            return;
        }

        if (body.has("name")) {
            success = adminService.updateFoodName(foodId, body["name"].s());
            if (!success) {
                crow::json::wvalue error;
                error["error"] = "Failed to update food name";
                res.code = 404;
                res.write(error.dump());
                res.end();
                return;
            }
        }

        if (body.has("price")) {
            success = adminService.updateFoodPrice(foodId, body["price"].d());
            if (!success) {
                crow::json::wvalue error;
                error["error"] = "Failed to update food price";
                res.code = 404;
                res.write(error.dump());
                res.end();
                return;
            }
        }

        crow::json::wvalue result;
        result["message"] = "Food updated successfully";
        res.code = 200;
        res.write(result.dump());
        res.end();
    });

    // DELETE /api/admin/foods/<int>
    CROW_ROUTE(app, "/api/admin/foods/<int>").methods("DELETE"_method)
    ([&adminService](const crow::request& req, crow::response& res, int foodId) {
        ADMIN_AUTH_CHECK(adminService, res);

        bool success = adminService.deleteFood(foodId);
        crow::json::wvalue result;
        if (success) {
            result["message"] = "Food deleted successfully";
            res.code = 200;
        } else {
            result["error"] = "Failed to delete food";
            res.code = 404;
        }
        res.write(result.dump());
        res.end();
    });

    // POST /api/admin/upload-city
    CROW_ROUTE(app, "/api/admin/upload-city").methods("POST"_method)
    ([&adminService](const crow::request& req, crow::response& res) {
        ADMIN_AUTH_CHECK(adminService, res);

        // Check if request has multipart data
        crow::multipart::message msg(req);
        
        // Find the uploaded file using the part_map
        auto it = msg.part_map.find("cityData");
        if (it == msg.part_map.end()) {
            crow::json::wvalue error;
            error["error"] = "No file uploaded. Please upload a file with name 'cityData'";
            res.code = 400;
            res.write(error.dump());
            res.end();
            return;
        }

        // Get file content
        std::string fileContent = it->second.body;
        if (fileContent.empty()) {
            crow::json::wvalue error;
            error["error"] = "Uploaded file is empty";
            res.code = 400;
            res.write(error.dump());
            res.end();
            return;
        }

        // Process the file content
        try {
            bool success = false;
            
            // Detect file format (JSON vs text)
            std::string trimmedContent = fileContent;
            trimmedContent.erase(0, trimmedContent.find_first_not_of(" \t\r\n"));
            
            if (trimmedContent[0] == '{' || trimmedContent[0] == '[') {
                // JSON format - process multiple cities
                std::cout << "🔍 Detected JSON format, processing multiple cities..." << std::endl;
                success = adminService.processCitiesJsonFile(fileContent);
            } else {
                // Text format - process single city (legacy support)
                std::cout << "🔍 Detected text format, processing single city..." << std::endl;
                success = adminService.processCityDataFile(fileContent);
            }
            
            crow::json::wvalue result;
            if (success) {
                result["message"] = "City data uploaded and processed successfully";
                res.code = 201;
            } else {
                result["error"] = "Failed to process city data file";
                res.code = 500;
            }
            res.write(result.dump());
            res.end();
        } catch (const std::exception& e) {
            crow::json::wvalue error;
            error["error"] = std::string("Error processing file: ") + e.what();
            res.code = 500;
            res.write(error.dump());
            res.end();
        }
    });
}

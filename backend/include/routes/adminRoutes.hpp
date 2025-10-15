/**
 * @file adminRoutes.hpp
 * @brief API route definitions for Admin-related endpoints
 */

 #ifndef ADMIN_ROUTES_HPP
 #define ADMIN_ROUTES_HPP
 
 #include "crow/crow_all.h"
 #include "../services/AdminService.hpp"
 
 /**
  * @brief Register all admin-related API routes
  * @param app Reference to Crow application instance
  * @param adminService Reference to AdminService for business logic
  * 
  * This function sets up all HTTP endpoints related to administrative operations, including:
  * - POST /admin/login - Admin authentication
  * - POST /admin/logout - Admin logout
  * - GET /admin/status - Check admin login status
  * - POST /admin/cities - Create new city (Admin only)
  * - PUT /admin/cities/{id} - Update city (Admin only)
  * - DELETE /admin/cities/{id} - Delete city (Admin only)
  * - POST /admin/foods - Create new food (Admin only)
  * - PUT /admin/foods/{id} - Update food (Admin only)
  * - DELETE /admin/foods/{id} - Delete food (Admin only)
  * - POST /admin/upload - Upload city data file (Admin only)
  * - GET /admin/cities - Get all cities (Admin only)
  * - GET /admin/foods - Get all foods (Admin only)
  */
 void registerAdminRoutes(crow::SimpleApp& app, AdminService& adminService);
 
 #endif
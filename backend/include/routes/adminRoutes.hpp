#ifndef ADMIN_ROUTES_HPP
#define ADMIN_ROUTES_HPP

#include "crow/crow_all.h"
#include "../services/AdminService.hpp"  // include AdminService

void registerAdminRoutes(crow::SimpleApp& app, AdminService& adminService);

#endif

# API-Only SQLite Database Makefile
# Builds the API server application only

CC = clang++
CFLAGS = -Wall -Wextra -std=c++17 -g

# Add Boost and Crow include paths
CFLAGS += -I/usr/local/include -I/opt/homebrew/include -Iinclude
LDFLAGS = -L/usr/local/lib -L/opt/homebrew/lib

# Link Boost libraries that Crow needs
LIBS = -lboost_thread -lboost_chrono -lpthread -lsqlite3

# Build directory
BUILD_DIR = build

# Core source files
DATABASE_SRC = src/databaseManager.cpp

# Entity source files
TRIPCITY_SRC = src/entities/TripCity.cpp
CITY_SRC = src/entities/City.cpp
FOOD_SRC = src/entities/Food.cpp
TRIP_SRC = src/entities/Trip.cpp
CITY_DISTANCE_SRC = src/entities/CityDistance.cpp
ADMIN_SRC = src/entities/Admin.cpp

# Repository source files
TRIPCITY_REPO_SRC = src/repositories/tripCityRepository.cpp
CITY_REPO_SRC = src/repositories/CityRepository.cpp
FOOD_REPO_SRC = src/repositories/FoodRepository.cpp
TRIP_REPO_SRC = src/repositories/TripRepository.cpp
CITY_DISTANCE_REPO_SRC = src/repositories/CityDistanceRepository.cpp

# Service source files
TRIPCITY_SERVICE_SRC = src/services/tripCityService.cpp
CITY_SERVICE_SRC = src/services/CityService.cpp
FOOD_SERVICE_SRC = src/services/FoodService.cpp
TRIP_SERVICE_SRC = src/services/TripService.cpp
ADMIN_SERVICE_SRC = src/services/AdminService.cpp

# API files
API_SRC = src/apis/CityApi.cpp
CITY_ROUTES_SRC = src/routes/cityRoutes.cpp
TRIP_ROUTES_SRC = src/routes/tripRoutes.cpp
ADMIN_ROUTES_SRC = src/routes/adminRoutes.cpp

# Object files
DATABASE_OBJ = $(BUILD_DIR)/databaseManager.o

# Entity object files
TRIPCITY_OBJ = $(BUILD_DIR)/TripCity.o
CITY_OBJ = $(BUILD_DIR)/City.o
FOOD_OBJ = $(BUILD_DIR)/Food.o
TRIP_OBJ = $(BUILD_DIR)/Trip.o
CITY_DISTANCE_OBJ = $(BUILD_DIR)/CityDistance.o
ADMIN_OBJ = $(BUILD_DIR)/Admin.o

# Repository object files
TRIPCITY_REPO_OBJ = $(BUILD_DIR)/tripCityRepository.o
CITY_REPO_OBJ = $(BUILD_DIR)/CityRepository.o
FOOD_REPO_OBJ = $(BUILD_DIR)/FoodRepository.o
TRIP_REPO_OBJ = $(BUILD_DIR)/TripRepository.o
CITY_DISTANCE_REPO_OBJ = $(BUILD_DIR)/CityDistanceRepository.o

# Service object files
TRIPCITY_SERVICE_OBJ = $(BUILD_DIR)/tripCityService.o
CITY_SERVICE_OBJ = $(BUILD_DIR)/CityService.o
FOOD_SERVICE_OBJ = $(BUILD_DIR)/FoodService.o
TRIP_SERVICE_OBJ = $(BUILD_DIR)/TripService.o
ADMIN_SERVICE_OBJ = $(BUILD_DIR)/AdminService.o

# API object files
API_OBJ = $(BUILD_DIR)/CityApi.o
CITY_ROUTES_OBJ = $(BUILD_DIR)/cityRoutes.o
TRIP_ROUTES_OBJ = $(BUILD_DIR)/tripRoutes.o
ADMIN_ROUTES_OBJ = $(BUILD_DIR)/adminRoutes.o

# API server executable
API_EXECUTABLE = api_server

# API OBJECT FILES
API_OBJS = $(API_OBJ) $(CITY_ROUTES_OBJ) $(TRIP_ROUTES_OBJ) $(DATABASE_OBJ) \
           $(CITY_OBJ) $(FOOD_OBJ) $(TRIP_OBJ) $(CITY_DISTANCE_OBJ) \
           $(CITY_REPO_OBJ) $(FOOD_REPO_OBJ) $(TRIP_REPO_OBJ) $(CITY_DISTANCE_REPO_OBJ) \
           $(CITY_SERVICE_OBJ) $(FOOD_SERVICE_OBJ) $(TRIP_SERVICE_OBJ) \
           $(TRIPCITY_REPO_OBJ) $(TRIPCITY_SERVICE_OBJ) $(TRIPCITY_OBJ) $(ADMIN_OBJ) \
		   $(ADMIN_SERVICE_OBJ) $(ADMIN_ROUTES_OBJ)
# Default target - Build API server
all: $(API_EXECUTABLE)
	@echo "🚀 API Server build completed successfully"

# Build API server
$(API_EXECUTABLE): $(API_OBJS)
	$(CC) $(CFLAGS) -o $(API_EXECUTABLE) $(API_OBJS) $(LDFLAGS) $(LIBS)
	@echo "✅ API server created: $(API_EXECUTABLE)"

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build database manager object file
$(DATABASE_OBJ): $(DATABASE_SRC) include/databaseManager.hpp include/databaseInterface.hpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(DATABASE_SRC) -o $(DATABASE_OBJ)

# ============================================================================
# ENTITY BUILD RULES
# ============================================================================
$(TRIPCITY_OBJ): $(TRIPCITY_SRC) include/entities/TripCity.hpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(TRIPCITY_SRC) -o $(TRIPCITY_OBJ)

$(CITY_OBJ): $(CITY_SRC) include/entities/City.hpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(CITY_SRC) -o $(CITY_OBJ)

$(FOOD_OBJ): $(FOOD_SRC) include/entities/Food.hpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(FOOD_SRC) -o $(FOOD_OBJ)

$(TRIP_OBJ): $(TRIP_SRC) include/entities/Trip.hpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(TRIP_SRC) -o $(TRIP_OBJ)

$(CITY_DISTANCE_OBJ): $(CITY_DISTANCE_SRC) include/entities/CityDistance.hpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(CITY_DISTANCE_SRC) -o $(CITY_DISTANCE_OBJ)

$(ADMIN_OBJ): $(ADMIN_SRC) include/entities/Admin.hpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(ADMIN_SRC) -o $(ADMIN_OBJ)

# ============================================================================
# REPOSITORY BUILD RULES
# ============================================================================
$(TRIPCITY_REPO_OBJ): $(TRIPCITY_REPO_SRC) include/repositories/TripCityRepository.hpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(TRIPCITY_REPO_SRC) -o $(TRIPCITY_REPO_OBJ)

$(CITY_REPO_OBJ): $(CITY_REPO_SRC) include/repositories/CityRepository.hpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(CITY_REPO_SRC) -o $(CITY_REPO_OBJ)

$(FOOD_REPO_OBJ): $(FOOD_REPO_SRC) include/repositories/FoodRepository.hpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(FOOD_REPO_SRC) -o $(FOOD_REPO_OBJ)

$(TRIP_REPO_OBJ): $(TRIP_REPO_SRC) include/repositories/TripRepository.hpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(TRIP_REPO_SRC) -o $(TRIP_REPO_OBJ)

$(CITY_DISTANCE_REPO_OBJ): $(CITY_DISTANCE_REPO_SRC) include/repositories/CityDistanceRepository.hpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(CITY_DISTANCE_REPO_SRC) -o $(CITY_DISTANCE_REPO_OBJ)

# ============================================================================
# SERVICE BUILD RULES
# ============================================================================
$(TRIPCITY_SERVICE_OBJ): $(TRIPCITY_SERVICE_SRC) include/services/tripCityService.hpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(TRIPCITY_SERVICE_SRC) -o $(TRIPCITY_SERVICE_OBJ)

$(CITY_SERVICE_OBJ): $(CITY_SERVICE_SRC) include/services/CityService.hpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(CITY_SERVICE_SRC) -o $(CITY_SERVICE_OBJ)

$(FOOD_SERVICE_OBJ): $(FOOD_SERVICE_SRC) include/services/FoodService.hpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(FOOD_SERVICE_SRC) -o $(FOOD_SERVICE_OBJ)

$(TRIP_SERVICE_OBJ): $(TRIP_SERVICE_SRC) include/services/TripService.hpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(TRIP_SERVICE_SRC) -o $(TRIP_SERVICE_OBJ)

$(ADMIN_SERVICE_OBJ): $(ADMIN_SERVICE_SRC) include/services/AdminService.hpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(ADMIN_SERVICE_SRC) -o $(ADMIN_SERVICE_OBJ)

# ============================================================================
# API BUILD RULES
# ============================================================================
$(API_OBJ): $(API_SRC) include/crow.h $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(API_SRC) -o $(API_OBJ)

$(CITY_ROUTES_OBJ): $(CITY_ROUTES_SRC) include/crow.h include/entities/City.hpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(CITY_ROUTES_SRC) -o $(CITY_ROUTES_OBJ)

$(TRIP_ROUTES_OBJ): $(TRIP_ROUTES_SRC) include/crow.h include/entities/Trip.hpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(TRIP_ROUTES_SRC) -o $(TRIP_ROUTES_OBJ)

$(ADMIN_ROUTES_OBJ): $(ADMIN_ROUTES_SRC) include/crow.h include/entities/Admin.hpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(ADMIN_ROUTES_SRC) -o $(ADMIN_ROUTES_OBJ)

# ============================================================================
# RUN TARGETS
# ============================================================================
# Run API server
run: $(API_EXECUTABLE)
	@echo "🚀 Starting API server on http://localhost:18080"
	./$(API_EXECUTABLE)

# ============================================================================
# UTILITY TARGETS
# ============================================================================
# Clean up
clean:
	rm -rf $(BUILD_DIR) $(API_EXECUTABLE)
	@echo "🧹 Cleaned build files"

# Test database connection
test-db: $(DATABASE_OBJ)
	@echo "✅ Database manager compiled successfully!"

# Debug build
debug: CFLAGS += -DDEBUG -O0
debug: $(API_EXECUTABLE)

# Release build
release: CFLAGS += -O2 -DNDEBUG
release: $(API_EXECUTABLE)

# Show build status
status:
	@echo "=== API-ONLY BUILD STATUS ==="
	@echo "Target: API Server ($(API_EXECUTABLE))"
	@echo "Entities: Trip, City, Food, TripCity, CityDistance"
	@echo "Repositories: Trip, City, Food, TripCity, CityDistance"
	@echo "Services: Trip, City, Food, TripCity"
	@echo "Routes: City, Trip"
	@echo "Build directory: $(BUILD_DIR)"
	@ls -la $(BUILD_DIR) 2>/dev/null || echo "Build directory not found - run 'make' first"

.PHONY: all clean run test-db debug release status
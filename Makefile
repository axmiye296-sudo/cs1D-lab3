# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude
API_CXXFLAGS = $(CXXFLAGS) -pthread -I/usr/include/jsoncpp

# Directories
SRC_DIR = src
OBJ_DIR = obj

# Target executables
TARGET = main
API_TARGET = api_server

# Find all source files recursively, excluding test files and api_server
MAIN_SRCS = $(shell find $(SRC_DIR) -name "*.cpp" ! -name "test_*.cpp" ! -name "api_server.cpp")
MAIN_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(MAIN_SRCS))

# API server source files (all sources except main.cpp and test files)
API_SRCS = $(shell find $(SRC_DIR) -name "*.cpp" ! -name "test_*.cpp" ! -name "main.cpp")
API_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(API_SRCS))

# Test source files
TEST_SRCS = $(shell find $(SRC_DIR) -name "*.cpp" ! -name "main.cpp" ! -name "api_server.cpp")
TEST_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(TEST_SRCS))

# Default target
all: $(TARGET)

# Rule to build the main executable
$(TARGET): $(MAIN_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lsqlite3

# Rule to build the API server
$(API_TARGET): $(API_OBJS)
	$(CXX) $(API_CXXFLAGS) -o $@ $^ -lsqlite3 -ljsoncpp

# Rule to compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Special rule for API server compilation with additional flags
$(OBJ_DIR)/api_server.o: $(SRC_DIR)/api_server.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(API_CXXFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -rf $(OBJ_DIR) $(TARGET) $(API_TARGET)

# Build API server
api: $(API_TARGET)

# Run the API server
run-api: $(API_TARGET)
	./$(API_TARGET)

# Build test executable
test: $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o test_tripCity $^ -lsqlite3
	./test_tripCity

# Run the application
run: $(TARGET)
	./$(TARGET)

# Debug build
debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

# Phony targets
.PHONY: all clean run debug test api run-api

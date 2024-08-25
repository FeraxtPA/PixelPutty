# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -I/usr/local/include

# Directories
BUILD_DIR = build
SRC_DIR = src
OBJ_DIR = $(BUILD_DIR)/obj
EXEC_DIR = $(BUILD_DIR)/exec

# Raylib paths
RAYLIB_DIR = /usr/local/lib
LDFLAGS = -L$(RAYLIB_DIR)/lib -lraylib -lGL -lm -lpthread

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Output executable
TARGET = $(EXEC_DIR)/PixelPutty

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	@mkdir -p $(EXEC_DIR)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -rf $(BUILD_DIR)

# Phony targets
.PHONY: all clean

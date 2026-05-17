# =========================================================
# CS415 Knapsack Project Makefile
# =========================================================

# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -Wall -Wextra -std=c++17 -g

# Project structure
SRC_DIR := src
BUILD_DIR := build
OUTPUT_DIR := output

# Executable name (placed in project root)
TARGET := p4

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Dependency files
DEPS := $(OBJS:.o=.d)

# =========================================================
# Default target
# =========================================================

all: directories $(TARGET)

# =========================================================
# Create required directories
# =========================================================

directories:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(OUTPUT_DIR)

# =========================================================
# Link executable
# =========================================================

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# =========================================================
# Compile source files
# =========================================================

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# =========================================================
# Include dependency files
# =========================================================

-include $(DEPS)

# =========================================================
# Run example
# =========================================================

run: all
	./$(TARGET) 1

# =========================================================
# Clean everything generated
# =========================================================

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(OUTPUT_DIR)
	rm -f $(TARGET)

# =========================================================
# Rebuild from scratch
# =========================================================

rebuild: clean all

# =========================================================
# Prevent conflicts with filenames
# =========================================================

.PHONY: all clean rebuild run directories
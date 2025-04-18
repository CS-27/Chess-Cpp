# Compiler and flags
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude -IC:/Users/chris/SFML-3.0.0/include

# SFML linking flags
LDFLAGS = -LC:/Users/chris/SFML-3.0.0/lib -lsfml-graphics -lsfml-window -lsfml-system -mwindows

# Project folders
SRC_DIR = C:/Users/chris/Documents/chessGame
BUILD_DIR = build
TARGET = chessgame

# Find all .cpp files recursively (works in Git Bash)
SRCS := $(shell find "$(SRC_DIR)" -name "*.cpp")

# Convert .cpp source files to .o object files in build/
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Default build
all: $(TARGET)

# Linking step
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS) -mconsole

# Compile .cpp to .o, creating build/ folders as needed
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
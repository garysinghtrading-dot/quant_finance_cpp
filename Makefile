# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra

# Directories
SRC_DIR = source
OBJ_DIR = obj
INC_DIR = include

# Files
TARGET = quant_program
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/csv_loader.cpp
OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/csv_loader.o

# Build rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean
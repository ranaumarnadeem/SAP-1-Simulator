# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./Components -I./Lib

# Directories
SRC_DIR = ./Components
LIB_DIR = ./Lib

# Source files
SRCS = core.cpp $(SRC_DIR)/RAM.cpp $(SRC_DIR)/Control_Unit.cpp $(SRC_DIR)/Register.cpp \
       $(SRC_DIR)/BUS.cpp $(SRC_DIR)/ALU.cpp $(LIB_DIR)/Utilities.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Output binary
TARGET = SAP-1-Simulator

# Build rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++20 -g
LDFLAGS := -lglfw -lGL -ldl
CC := gcc
CFLAGS := -g

# Directories
OBJ_DIR := obj
CORE_DIR := core
SYSTEMS_DIR := systems
PLATFORM_DIR := platform
RENDERER_DIR := renderer

# Source files
MAIN_SRC := main.cpp world.cpp
GLAD_SRC := glad.c
CORE_SRCS := $(wildcard $(CORE_DIR)/*.cpp)
SYSTEMS_SRCS := $(wildcard $(SYSTEMS_DIR)/*.cpp)
PLATFORM_SRCS := $(wildcard $(PLATFORM_DIR)/*.cpp)
RENDERER_SRCS := $(wildcard $(RENDERER_DIR)/*.cpp)

# Object files mapped to obj/
OBJS := $(addprefix $(OBJ_DIR)/, \
	$(MAIN_SRC:.cpp=.o) \
	$(GLAD_SRC:.c=.o) \
	$(CORE_SRCS:.cpp=.o) \
	$(SYSTEMS_SRCS:.cpp=.o) \
	$(PLATFORM_SRCS:.cpp=.o) \
	$(RENDERER_SRCS:.cpp=.o))

# Executable name
TARGET := main

# Default target
all: $(TARGET)

# Link all object files
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Compile .cpp files into obj/
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile .c files into obj/
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean


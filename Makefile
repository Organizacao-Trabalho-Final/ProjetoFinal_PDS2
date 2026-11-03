CC = g++
FLAGS = -std=c++11 -Wall -Wextra -pedantic

SRC_DIR = src
INC_DIR = include
OBJ_DIR = build

LIBS = -I$(INC_DIR)

INCLUDE = $(wildcard $(INC_DIR)/*.hpp)
SOURCE  = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCE))

TARGET = biblioteca

all: $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDE) | $(OBJ_DIR)
	$(CC) $(FLAGS) $(LIBS) $< -c -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(FLAGS) $(LIBS) $(OBJECTS) -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

docs:
	doxygen Doxyfile

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all objects docs clean

	


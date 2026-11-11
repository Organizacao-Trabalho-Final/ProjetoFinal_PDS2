CC = g++
FLAGS = -std=c++11 -Wall -Wextra -pedantic

SRC_DIR = src
INC_DIR = include
OBJ_DIR = build

LIBS = -I$(INC_DIR) -Ithird_party

INCLUDE = $(wildcard $(INC_DIR)/*.hpp)
CORE_SOURCE = $(wildcard $(SRC_DIR)/*.cpp)
CORE_OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(CORE_SOURCE))
MAIN_OBJECTS = $(OBJ_DIR)/main.o
OBJECTS = $(CORE_OBJECTS) $(MAIN_OBJECTS)

TEST_SOURCE = $(wildcard tests/*/*.cpp)
TEST_TARGETS = $(patsubst tests/%.cpp, $(OBJ_DIR)/tests/%, $(TEST_SOURCE))

TARGET = biblioteca

all: $(TARGET)

objects: $(OBJECTS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDE) | $(OBJ_DIR)
	$(CC) $(FLAGS) $(LIBS) $< -c -o $@

$(MAIN_OBJECTS): main.cpp $(INCLUDE) | $(OBJ_DIR)
	$(CC) $(FLAGS) $(LIBS) $< -c -o $@
	
$(TARGET): $(OBJECTS)
	$(CC) $(FLAGS) $(LIBS) $(OBJECTS) -o $@

$(OBJ_DIR)/tests/%: tests/%.cpp $(CORE_OBJECTS) $(INCLUDE)
	mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(LIBS) $< $(CORE_OBJECTS) -o $@

test: $(TEST_TARGETS)
	@for teste in $(TEST_TARGETS); do echo "Executando $$teste"; ./$$teste || exit 1; done

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

docs:
	doxygen Doxyfile

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all objects docs test clean

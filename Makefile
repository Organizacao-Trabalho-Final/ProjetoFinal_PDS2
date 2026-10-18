CC      = g++
MC      = moc
QT_FLAG = $(shell pkg-config --cflags Qt5Widgets)
QT_LIBS = $(shell pkg-config --libs Qt5Widgets)
FLAGS   = -std=c++11 -fPIC $(QT_FLAG)

SRC_DIR     = src
SRC_MOC_DIR = src/mocs
INC_DIR     = include
INC_MOC_DIR = include/ui
OBJ_DIR     = build
OBJ_MOC_DIR = build/mocs

LIBS     = -I$(INC_DIR)
LIBS_MOC = -I$(INC_MOC_DIR)

################### LISTAS #####################
INCLUDE      = $(wildcard $(INC_DIR)/*.hpp)
INCLUDE_MOC  = $(wildcard $(INC_MOC_DIR)/*.hpp)
SOURCE       = $(wildcard $(SRC_DIR)/*.cpp)
################################################

################################### SUBSTITUIÇÔES ########################################
SOURCE_MOC   = $(patsubst $(INC_MOC_DIR)/%.hpp, $(SRC_MOC_DIR)/moc_%.cpp, $(INCLUDE_MOC))
OBJECTS_MOC  = $(patsubst $(SRC_MOC_DIR)/moc_%.cpp, $(OBJ_MOC_DIR)/moc_%.o, $(SOURCE_MOC))
OBJECTS      = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCE))
##########################################################################################

TARGET = $(SRC_DIR)/main

all: $(TARGET)

$(SRC_MOC_DIR)/moc_%.cpp: $(INC_MOC_DIR)/%.hpp | $(SRC_MOC_DIR)
	$(MC) $(LIBS) $(LIBS_MOC) $< -o $@

$(OBJ_MOC_DIR)/moc_%.o: $(SRC_MOC_DIR)/moc_%.cpp
	mkdir -p  $(OBJ_MOC_DIR)
	$(CC) $(FLAGS) $(LIBS) $(LIBS_MOC) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDE) | $(OBJ_DIR)
	$(CC) $(FLAGS) $(QT_LIBS) $(LIBS) $(LIBS_MOC) $< -c -o $@

$(TARGET) : $(OBJECTS) $(OBJECTS_MOC) | $(OBJ_DIR)
	$(CC) $(FLAGS) $(LIBS) $(OBJECTS) $(OBJECTS_MOC) $(QT_LIBS) -o ./main

$(OBJ_DIR) $(SRC_MOC_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) $(SRC_MOC_DIR) ./main

	


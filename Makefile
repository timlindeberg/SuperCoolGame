CC = g++

FLAGS = -g -std=gnu++0x -Wall

HEADER_FOLDER 	:= src/headers
SRC_FOLDER   	:= src/implementation
BIN_FOLDER	  	:= bin
OBJ_FOLDER		:= $(BIN_FOLDER)/obj

CPP := $(wildcard $(SRC_FOLDER)/*.cpp)
OBJ := $(CPP:$(SRC_FOLDER)/%.cpp=$(OBJ_FOLDER)/%.o)
HPP := $(CPP:$(SRC_FOLDER)/%.cpp=$(HEADER_FOLDER)/%.hpp)

vpath %.cpp $(SRC_FOLDER)
vpath %.hpp $(HEADER_FOLDER)

all: $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(BIN_FOLDER)/Game.out

${OBJ_FOLDER}/%.o: %.cpp %.hpp
	$(CC) $(FLAGS) -I$(HEADER_FOLDER) -c $< -o $@

clean:
	rm -rf $(OBJ_FOLDER)/*o
	rm -rf $(BIN_FOLDER)/*out

rebuild: clean all
CC = g++

FLAGS = -g -O2 -std=gnu++0x

HEADER_FOLDER := src/headers
IMPL_FOLDER   := src/implementation

FILES = Utils IO Environment Actor Entity Game Format Parser




HPP := $(addprefix $(HEADER_FOLDER)/, $(FILES))
HPP := $(addsuffix .hpp, $(HPP))

CPP := $(addprefix $(IMPL_FOLDER)/, $(FILES))
CPP := $(addsuffix .cpp, $(CPP))

bin/Test.out: $(CPP) $(HPP) $(IMPL_FOLDER)/Test.cpp $(IMPL_FOLDER)/IO.tpp
	g++ $(IMPL_FOLDER)/Test.cpp $(CPP) -o bin/Test.out $(FLAGS) -I$(HEADER_FOLDER) -I$(IMPL_FOLDER) -D=TEST

bin/Game.out: $(CPP) $(HPP) $(IMPL_FOLDER)/IO.tpp
	g++ $(CPP) -o bin/Game.out $(FLAGS) -I$(HEADER_FOLDER) -I$(IMPL_FOLDER)
FLAGS = -g -O2 -std=gnu++0x

HEADER_FOLDER := src/headers
IMPL_FOLDER   := src/implementation

FILES = Utils Environment Actor Entity IO Game




HPP := $(addprefix $(HEADER_FOLDER)/, $(FILES))
HPP := $(addsuffix .hpp, $(HPP))

CPP := $(addprefix $(IMPL_FOLDER)/, $(FILES))
CPP := $(addsuffix .cpp, $(CPP))

bin/Test.out: $(CPP) $(HPP) $(IMPL_FOLDER)/Test.cpp
	g++ $(IMPL_FOLDER)/Test.cpp $(CPP) -o bin/Test.out $(FLAGS) -I$(HEADER_FOLDER) -D=TEST

bin/Game.out: $(CPP) $(HPP)
	g++ $(CPP) -o bin/Game.out $(FLAGS) -I$(HEADER_FOLDER)
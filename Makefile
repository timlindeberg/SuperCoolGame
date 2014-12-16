FLAGS = -g -O2 -std=gnu++0x

CPP = Entity.cpp Saveable.cpp
HPP = Actor.hpp Entity.hpp Saveable.hpp 


SRCFOLDER := src
CPP := $(addprefix $(SRCFOLDER)/, $(CPP))
HPP := $(addprefix $(SRCFOLDER)/, $(HPP))


Test: $(CPP) $(HEADERS)
	g++ src/Test.cpp $(CPP) -o bin/Main.out $(FLAGS)
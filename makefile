CC = g++
OBJFOLDER = obj
CPPVER = -std=c++2a
FILES := $(wildcard main.cpp network.cpp population.cpp nodeGene.cpp connectionGene.cpp util.cpp config.cpp species.cpp)
HPPFILES := $(wildcard Activations.hpp)
OBJECTS := $(patsubst %.cpp,$(OBJFOLDER)/%.o,$(FILES))
#objects := $(patsubst %.cpp,$(OBJFOLDER)/%.o,$(wildcard *.cpp)) all cpp files in directory

all : $(OBJECTS)
	@echo linking
	@$(CC) $(CPPVER) $(OBJECTS) $(Activations) -o main

$(OBJFOLDER)/main.o: main.cpp
	@echo building main
	@mkdir -p obj
	@$(CC) $(CPPVER) -c main.cpp -o $(OBJFOLDER)/main.o

$(OBJFOLDER)/%.o: %.cpp %.h
	@echo building $<
	@$(CC) $(CPPVER) -c $< -o $@

clean:
	rm $(OBJFOLDER)/* main

#Author: Justin Tromp
#01/10/2019
#.PHONY and code below that point in this makefile is referenced through:
#Title: makefile
#Author: Harlan James (TA at OSU)
#Date: 01/10/2019
#Code Version:
#Availability: Oregon State University (Canvas)

#Project Name
PROJECT = Final_Project

#Compiler
#C=g++                                  #Use for C
CXX=g++

#Options to be passed/compiler flags
#CFLAGS=-pedantic -std=gnu++11 -Wall    #Use for C
LDFLAGS=-lboost_date_time
CXXFLAGS=-pedantic
CXXFLAGS+=-std=gnu++11
CXXFLAGS+=-Wall
#CXXFLAGS+=-03

#Source files
SOURCES=main.cpp ExitPoint.cpp Game.cpp GamePiece.cpp Map.cpp Outdoors.cpp Player.cpp Space.cpp Wall.cpp GroceryStore.cpp OutdoorRecSupplier.cpp inputValidation.cpp Floor.cpp Knife.cpp Zombie.cpp Key.cpp Medicine.cpp ExitPoint.cpp Field.cpp Door.cpp

#Header files
HEADERS=ExitPoint.hpp Game.hpp GamePiece.hpp Map.hpp Outdoors.hpp Player.hpp Space.hpp Wall.hpp GroceryStore.hpp OutdoorRecSupplier.hpp inputValidation.hpp Floor.hpp Knife.hpp Zombie.hpp Key.hpp Medicine.hpp ExitPoint.hpp Field.hpp Door.hpp

#Objects
OBJECTS=$(SOURCES:.cpp=.o)

#Output Binary
BINARY=$(PROJECT).bin

#Valgrind Options
VALGRIND= --leak-check=full --show-leak-kinds=all --tool=memcheck --track-origins=yes

#Executable name
EXECUTABLE=Final_Project


.PHONY: default debug clean zip

default: clean $(BINARY) debug


debug: $(BINARY)
	@valgrind $(VALGRIND) ./$(BINARY)

$(BINARY): $(OBJECTS)
	@echo "CXX	$@"
	@$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	@echo "CXX	$^"
	@$(CXX) $(CXXFLAGS) -c $^

zip:
	zip $(PROJECT).zip *.cpp *.hpp makefile *.pdf *.txt

clean: $(CLEAN)
	@echo "RM	*.o"
	@echo "RM	$(BINARY)"
	@rm -f *.o $(BINARY)
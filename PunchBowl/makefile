#
# Makefile for Dragonfly Egg library and test programs
#
# Copyright Mark Claypool and WPI, 2015
#
# Modified by Lambert Wang for IMGD3000 Project 2: Dragonfly
#
# Usage instructions located in ../readme.txt

CC= g++
LINK= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lGLEW -lrt

# path to dragonfly includes
INCLUDE= -I../../dragonfly-lwang5/include 

# Location of dragonfly engine
ENGINE= ../../dragonfly-lwang5/lib/dragonfly-lwang5-linux64.a 

# Location of engine code
GAMESRC= \
		../include/character/Character.cpp \
		../include/character/CharTest.cpp \
		../include/stage/Stage.cpp \
		../include/stage/UltimateTerminal.cpp \
		../include/Platform.cpp \
		../include/Organizer.cpp \
		../include/GameStart.cpp \

GAMEFILES= $(GAMESRC:.cpp=.o)

# Main game program
MAINGAME= ../include/game.cpp
EXECUTABLE= punchbowl

all: clear $(EXECUTABLE) makefile

$(EXECUTABLE): $(ENGINE) $(GAMEFILES) $(MAINGAME) $(GAMESRC)
	$(CC) $(WARN) $(MAINGAME) $(GAMEFILES) $(ENGINE) -o $@ $(INCLUDE) $(LINK) -std=c++11

.cpp.o: 
	$(CC) $(WARN) -c $(INCLUDE) $< -o $@ -std=c++11

clean:
	rm -rf dragonfly.log Makefile.bak $(GAMEFILES) $(EXECUTABLE)

clear:
	clear

depend: 
	makedepend *.cpp 2> /dev/null

# DO NOT DELETE

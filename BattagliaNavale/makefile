#Makefile??


CXX = g++
CXXFLAGS = -Wall -std=c++11
GCCVERSION = $(shell gcc -dumpversion)

ifeq "$(GCCVERSION)" "4.8.5"
	CXXFLAGS += -D_GLIBCXX_USE_CXX11_ABI=0
endif
RM = rm -f
all: battaglia
battaglia: main.o Tabella.o Nave.o Player.o Game.o Coordinate.o
	$(CXX) $(CXXFLAGS) -o battaglia  main.o Tabella.o Nave.o Player.o Game.o Coordinate.o
main.o: main.cpp Tabella.h Nave.h Player.h Coordinate.h
	$(CXX) $(CXXFLAGS) -c main.cpp
Tabella.o: Tabella.cpp Tabella.h
	$(CXX) $(CXXFLAGS) -c Tabella.cpp
Nave.o: Nave.cpp Nave.h
	$(CXX) $(CXXFLAGS) -c Nave.cpp
Player.o: Player.cpp Player.h Nave.h Tabella.h
	$(CXX) $(CXXFLAGS) -c Player.cpp
Game.o: Game.cpp Game.h
	$(CXX) $(CXXFLAGS) -c Game.cpp
Coordinate.o: Coordinate.cpp Coordinate.h
	$(CXX) $(CXXFLAGS) -c Coordinate.cpp
clean:
	$(RM) *.o

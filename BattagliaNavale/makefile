#Makefile??


CXX = g++
CXXFLAGS = -Wall
RM = rm -f
all: battaglia
battaglia: main.o Tabella.o Nave.o Player.o
	$(CXX) $(CXXFLAGS) -o battaglia  main.o Tabella.o Nave.o Player.o
main.o: main.cpp Tabella.h Nave.h Player.h
	$(CXX) $(CXXFLAGS) -c main.cpp
Tabella.o: Tabella.cpp Tabella.h
	$(CXX) $(CXXFLAGS) -c Tabella.cpp
Nave.o: Nave.cpp Nave.h
	$(CXX) $(CXXFLAGS) -c Nave.cpp
Player.o: Player.cpp Player.h Nave.h Tabella.h
	$(CXX) $(CXXFLAGS) -c Player.cpp
clean:
	$(RM) *.o

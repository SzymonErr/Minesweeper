CC = g++

CFLAGS = -g -Wall -std=c++11

all: saper

clean:
	rm -f *.o saper
	
saper: main.o Singletile.o Board.o Gameplay.o
	$(CC) $(CFLAGS) -o saper main.o Singletile.o Board.o Gameplay.o
	
main.o: main.cpp Singletile.h Board.h Gameplay.h
	$(CC) $(CFLAGS) -c main.cpp
	
Gameplay.o: Gameplay.cpp Board.h
	$(CC) $(CFLAGS) -c Gameplay.cpp
	
Board.o: Board.cpp Singletile.h
	$(CC) $(CFLAGS) -c Board.cpp 
	
Singletile.o: Singletile.cpp
	$(CC) $(CFLAGS) -c Singletile.cpp
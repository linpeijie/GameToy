# $ make
# $ ./fighter

CC = g++
CFLAGS = -c
STD = -std=c++17
DEBUG = -g
SFML = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all: fighter

fighter: Entity.o Player.o Enemy.o Game.o main.o
	$(CC) $(STD) $(DEBUG) Entity.o Player.o Enemy.o Game.o main.o -o fighter $(SFML)

main.o : main.cpp
	$(CC) $(STD) $(CFLAGS) $(DEBUG) main.cpp

Game.o : Game.cpp
	$(CC) $(STD) $(CFLAGS) $(DEBUG) Game.cpp

Entity.o : Entity.cpp
	$(CC) $(STD) $(CFLAGS) $(DEBUG) Entity.cpp

Player.o : Player.cpp
	$(CC) $(STD) $(CFLAGS) $(DEBUG) Player.cpp

Enemy.o : Enemy.cpp
	$(CC) $(STD) $(CFLAGS) $(DEBUG) Enemy.cpp

.PHONY: clean
clean:
	-rm *.o fighter

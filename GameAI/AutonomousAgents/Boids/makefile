# $ make
# $ ./boids

CC = g++
CFLAGS = -c
STD = -std=c++11
DEBUG = -g
SFML = -lsfml-graphics -lsfml-window -lsfml-system

all: boids

boids: Boid.o Flock.o Vector2D.o main.o World.o
	$(CC) $(STD) $(DEBUG) Boid.o Flock.o Vector2D.o World.o main.o -o boids $(SFML)

Boid.o : Boid.cpp
	$(CC) $(STD) $(CFLAGS) $(DEBUG) Boid.cpp

Flock.o : Flock.cpp
	$(CC) $(STD) $(CFLAGS) $(DEBUG) Flock.cpp

Vector2D.o : Vector2D.cpp
	$(CC) $(STD) $(CFLAGS) $(DEBUG) Vector2D.cpp

World.o : World.cpp
	$(CC) $(STD) $(CFLAGS) $(DEBUG) World.cpp

.PHONY: clean
clean:
	-rm *.o boids

tar:
	tar cfv boids.tar \
	Vector2D.h Vector2D.cpp \
	Boid.h Boid.cpp \
	Flock.h Flock.cpp \
	World.cpp World.h

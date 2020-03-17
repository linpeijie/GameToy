# $ make
# $ ./boids

CC = g++
CFLAGS = -c
STD = -std=c++11
DEBUG = -g
SFML = -lsfml-graphics -lsfml-window -lsfml-system

all: boids

boids: main.o World.o
	$(CC) $(STD) $(DEBUG) World.o main.o -o boids $(SFML)

# Boid.o : Boid.cpp
# 	$(CC) $(CFLAGS) $(DEBUG) Boid.cpp

# Pvector.o : Pvector.cpp
# 	$(CC) $(CFLAGS) $(DEBUG) Pvector.cpp

# Flock.o : Flock.cpp
# 	$(CC) $(CFLAGS) $(DEBUG) Flock.cpp

World.o : World.cpp
	$(CC) $(STD) $(CFLAGS) $(DEBUG) World.cpp

clean:
	rm edit *.o boids

tar:
	tar cfv boids.tar World.cpp World.h
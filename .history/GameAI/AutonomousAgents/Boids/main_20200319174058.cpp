#include <iostream>
#include "World.h"

int main()
{
    World world;

    sf::Clock clock;
    world.run(clock);

    return 0;
}


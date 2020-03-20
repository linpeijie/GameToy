#include <iostream>
#include "B.h"

int main()
{
    B b;

    b(1, 2);

    std::cout << b.x << b.y << std::endl;
}
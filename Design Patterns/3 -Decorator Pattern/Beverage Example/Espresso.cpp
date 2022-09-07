#include "Headers/Espresso.h"
#include <iostream>
Espresso::Espresso ()
{
    description ="Espresso";
}
double Espresso::cost()
{
    return 0.99;
}
Espresso::~Espresso()
{
    std::cout<<"~Espresso()\n";
}
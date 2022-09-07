#include "Headers/HouseBlend.h"
#include <iostream>
HouseBlend::HouseBlend  ()
{
    description ="HouseBlend";
}
double HouseBlend::cost()
{
    return 0.99;
}
HouseBlend::~HouseBlend ()
{
    std::cout<<"~HouseBlend()\n";
}
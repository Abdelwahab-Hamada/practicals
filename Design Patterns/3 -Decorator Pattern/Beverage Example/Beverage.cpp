#include "Headers/Beverage.h"
#include <iostream>
#include <string>
Beverage::Beverage ()
{
    description = "Unknown Beverage";
}

string Beverage::getDescription()
{
    return description;
}

Beverage::~Beverage ()
{
    std::cout<<"~Beverage()\n";
}
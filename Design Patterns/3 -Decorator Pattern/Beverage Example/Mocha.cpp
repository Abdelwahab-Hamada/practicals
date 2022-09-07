#include "Headers/Beverage.h"
#include "Headers/Mocha.h"
#include<iostream>
Mocha::Mocha (Beverage*Beve):Beve_(Beve)
{
}
string Mocha::getDescription()
{
    return Beve_->getDescription()+" with Mocha";
}
double Mocha::cost()
{
    return Beve_->cost()+0.49;
}
Mocha::~Mocha ()
{
    std::cout<<"~Mocha()\n";
    delete Beve_;
}
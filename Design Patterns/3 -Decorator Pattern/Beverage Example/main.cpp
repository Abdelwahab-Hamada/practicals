#include "Headers/Beverage.h"
#include "Headers/CondimentDecorator.h"
#include "Headers/Espresso.h"
#include "Headers/Mocha.h"
#include "Headers/HouseBlend.h"
#include <iostream>

int main()
{
    Beverage *Beverage1 =new Espresso ();
    std::cout<<"Order 1 \n"<<"Beverage : "<<Beverage1->getDescription()<<endl;
    std::cout<<"Cost :"<<Beverage1->cost()<<"$\n";
    
    Beverage *Beverage2 =new HouseBlend ();
    Beverage2 =new Mocha(Beverage2);
    std::cout<<"Order 2 \n"<<"Beverage : "<<Beverage2->getDescription()<<endl;
    std::cout<<"Cost :"<<Beverage2->cost()<<"$\n";
  
    delete Beverage1;
    delete Beverage2;
    
    return 0;
}
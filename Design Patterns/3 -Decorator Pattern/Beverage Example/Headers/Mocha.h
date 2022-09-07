#ifndef MOCHA_H
#define MOCHA_H
#include "Beverage.h"
#include "CondimentDecorator.h"
#include <string>
class Mocha : public CondimentDecorator
{
private:    
    Beverage*Beve_;
public:
    Mocha (Beverage* );
    string getDescription ();
    double cost();
    ~Mocha ();  
};
#endif
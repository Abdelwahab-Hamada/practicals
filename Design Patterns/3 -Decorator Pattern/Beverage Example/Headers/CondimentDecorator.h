#ifndef CONDIMENTDECORATOR_H
#define CONDIMENTDECORATOR_H
#include "Beverage.h"
#include <string>
class CondimentDecorator : public Beverage
{
public:    
    virtual string getDescription () =0;
    virtual~CondimentDecorator ();
};
#endif
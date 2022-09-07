#ifndef STATE_H
#define STATE_H
#include "GUMBALLMACHINE.h"
class STATE
{
public:    
    virtual void insertQuarter () =0;
    virtual void ejectQuarter () =0;
    virtual void turnCrank () =0;
    virtual void dispense () =0;    
};

#endif
#ifndef NQ_STATE_H
#define NQ_STATE_H
#include "STATE.h"
#include "GUMBALLMACHINE.h"
#include <iostream>

class NQ_STATE : public STATE
{
    GUMBALLMACHINE* gbm_;
    
public:    
    NQ_STATE (GUMBALLMACHINE gbm) 
    : gbm_(gbm)
    { }
    
    void insertQuarter ()
    {
        std::cout<<"Quarter have been "
                 <<"inserted\n";
        gbm_.setState 
        (gbm_.getHasQuarterState);
    }
    
    void ejectQuarter ()
    {
        std::cout<<"You haven't inserted a "
                 <<"Quarter\n";
    }
    
    void turnCrank ()
    {
        std::cout<<"You turned ,but there's "
                 <<"no Quarter\n";
    }
    
    void dispense ()
    {
        std::cout<<"You need to pay first\n";
    }
        
};

#endif
#ifndef HQ_STATE_H
#define HQ_STATE_H
#include "STATE.h"
#include "GUMBALLMACHINE.h"
#include <iostream>

class HQ_STATE : public STATE
{
    GUMBALLMACHINE* gbm_;
    
public:    
    HQ_STATE (GUMBALLMACHINE* gbm) 
    : gbm_(gbm)
    { }
    
    void insertQuarter ()
    {
        std::cout<<"You can't insert another "
                 <<"Quarter\n";         
    }
    
    void ejectQuarter ()
    {
        std::cout<<"Quarter returned\n";
        gbm_->setState 
        (gbm_->getNoQuarterState());
    }
    
    void turnCrank ()
    {
        std::cout<<"You turned... \n";
        gbm_->setState (gbm_->getSoldState());
    }
    
    void dispense ()
    {
        std::cout<<"No Gumball dispensed\n";
    }
};

#endif
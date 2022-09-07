#ifndef S_STATE_H
#define S_STATE_H
#include "STATE.h"
#include "GUMBALLMACHINE.h"
#include <iostream>

class S_STATE : public STATE
{
    GUMBALLMACHINE* gbm_;
    
public:    
    HQ_STATE (GUMBALLMACHINE gbm) 
    : gbm_(gbm)
    { }
    
    void insertQuarter ()
    {
        std::cout<<"Please wait,you have been"
                 <<"gaven Gumball \n"; 
    }
    
    void ejectQuarter ()
    {
        std::cout<<"You Already turned the "
                 <<"crank\n";
    }
    
    void turnCrank ()
    {
        std::cout<<"Turned crank twice "
                 <<"doesn't get you more\n";
    }
    
    void dispense ()
    {
        gbm_->releaseBall();
        if (gbm_->getCounter() > 0)
            gbm_->setState 
            (gbm_->getNoQuarterState());
        else
        {
            std::cout<<"Oops,out of Gums\n";
            gbm_->setState 
            (gbm_->getSoldOutState());
        }
    }
};

#endif
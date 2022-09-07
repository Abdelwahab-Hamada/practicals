#ifndef SO_STATE_H
#define SO_STATE_H
#include <iostream>
#include "STATE.h"
#include "GUMBALLMACHINE.h"

class SO_STATE : public STATE
{
    class GUMBALLMACHINE* gbm_;
    
public:
    SO_STATE (class GUMBALLMACHINE* gbm) : 
    gbm_(gbm)
    { }
    
    void insertQuarter ()
    {
        std::cout<<"You Can't insert Quarter "
                 <<"GumballsMachine Empty\n";
        gbm_->setState 
        (gbm_->getHasQuarterState());
    }
    
    void ejectQuarter ()
    {
        std::cout<<"Can't Eject,you haven't"
                 <<"insert Quarter yet\n";
    }
    
    void turnCrank ()
    {
        std::cout<<"You turned ,but there's "
                 <<"no Gumballs\n";
    }
    
    void dispense ()
    {
        std::cout<<"No Gumball dispensed\n";
    }        
};

#endif
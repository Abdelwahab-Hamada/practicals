#ifndef GUMBALLMACHINE_H
#define GUMBALLMACHINE_H

#include <iostream>
#include "STATE.h"
#include "SO_STATE.h"
#include "NQ_STATE.h"
#include "HQ_STATE.h"
#include "S_STATE.h"

class GUMBALLMACHINE
{
private:    
    class STATE *soldOutState;
    class STATE *noQuarterState;
    class STATE *hasQuarterState;
    class STATE *soldState;
    
    class STATE *state;
    int count_ =0;
    
public:
    GUMBALLMACHINE (int count)
    {
    soldOutState =new SO_STATE(this );
    noQuarterState =new NQ_STATE(this );
    hasQuarterState =new HQ_STATE(this );
    soldState =new S_STATE(this );      
       
        if (count_ > 0)
        {
            state =noQuarterState;
        }
    }
    
    void insertQuarter ()
    {
        state->insertQuarter();
    }
    
    void ejectQuarter ()
    {
        state->ejectQuarter();
    }
    
    void turnCrank ()
    {
        state->turnCrank();
    }
    
    void dispense ()
    {
        state->dispense();
    }
    
    void setState (STATE *state)
    {
        this->state =state;
    }
    
    void releaseBall ()
    {
        std::cout<<"Gumball comes rolling out"
                 <<" the slot";
        if (count_ != 0)         
            count_--;
    }
    
    int getCounter ()
    {
        return count_;
    }
    
    STATE* getSoldOutState ()
    {
        return soldOutState;
    }
    
    STATE* getNoQuarterState ()
    {
        return noQuarterState;
    }
    
    STATE* getHasQuarterState ()
    {
        return hasQuarterState;
    }
    
    STATE* getSoldState ()
    {
        return soldState;
    }
};

#endif
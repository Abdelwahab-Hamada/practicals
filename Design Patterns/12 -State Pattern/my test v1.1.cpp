#include <iostream>

class STATE
{
public:
//Requestes    
    virtual void insertQuarter () =0;
    virtual void ejectQuarter () =0;
    virtual void turnCrank () =0;
    virtual void dispense () =0;    
};

class GUMBALLMACHINE //Context
{
    class STATE *soldOutState;
    class STATE *noQuarterState;
    class STATE *hasQuarterState;
    class STATE *soldState;
    
    class STATE *state =soldOutState;
    int count_ =0;
    
public: 
    GUMBALLMACHINE (int count);
    
    void setState (STATE *state)
    {
        this->state =state;
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
    
    void releaseBall ()
    {
        std::cout<<"Gumball comes rolling out"
                 <<" the slot";
        if (count_ != 0)         
            count_--;
        std::cout<<"\nGumballs :" 
        <<getCounter()<<"\n";
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


class SO_STATE : public STATE
{
    GUMBALLMACHINE* gbm_;
    
public:
    SO_STATE (GUMBALLMACHINE* gbm) 
    : gbm_(gbm)
    { }
    
    void insertQuarter ()
    {
        std::cout<<"You Can't insert Quarter "
                 <<"GumballsMachine Empty\n";
        gbm_->setState 
        (gbm_->getHasQuarterState());
        //gbm_->ejectQuarter();
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

class NQ_STATE : public STATE
{
    GUMBALLMACHINE* gbm_;
    
public:    
    NQ_STATE (GUMBALLMACHINE* gbm) 
    : gbm_(gbm)
    { }
    
    void insertQuarter ()
    {
        std::cout<<"Quarter have been "
                 <<"inserted\n";
        gbm_->setState 
        (gbm_->getHasQuarterState());
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
        gbm_->ejectQuarter();         
    }
    
    void ejectQuarter ()
    {
        std::cout<<"Quarter returned\n";
        gbm_->setState 
        (gbm_->getNoQuarterState());
    }
    
    void turnCrank ()
    {
        std::cout<<"Crank been turned... \n";
        gbm_->setState (gbm_->getSoldState());
        gbm_->releaseBall();
    }
    
    void dispense ()
    {
        std::cout<<"No Gumball dispensed\n";
        std::cout<<"You have to turn Crank"
                 <<" but i will do\n";
        gbm_->turnCrank();
    }
};

class S_STATE : public STATE
{
    GUMBALLMACHINE* gbm_;
    
public:    
    S_STATE (GUMBALLMACHINE* gbm) 
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
                 <<"crank, can't eject\n";
    }
    
    void turnCrank ()
    {
        std::cout<<"Turned crank twice "
                 <<"doesn't get you more\n";
    }
    
    void dispense ()
    {                
        if (gbm_->getCounter() > 0)
            gbm_->setState 
            (gbm_->getNoQuarterState());
        else
        {
            std::cout<<"Now All Gums sold\n";
            gbm_->setState 
            (gbm_->getSoldOutState());
        }
    }
};

GUMBALLMACHINE::GUMBALLMACHINE (int count) 
{
    this->count_ =count;
    std::cout<<"Inventory :" 
    <<this->getCounter()<<"\n\n";
    soldOutState =new SO_STATE(this );
    noQuarterState =new NQ_STATE(this );
    hasQuarterState =new HQ_STATE(this );
    soldState =new S_STATE(this );
    
    if (count_ >0)
        state =noQuarterState;
}

class COMMAND
{
public:    
    virtual void Do() =0;
    virtual void unDo() =0;
};

class NON :public COMMAND
{
public:    
    void Do ()
    {}
    
    void unDo ()
    {}
};

class GBMCONTROL //invocer
{
    COMMAND *slot;
    
public:    
    GBMCONTROL ()
    {
        this->slot =new NON ();
    }
    
    void setSlot (COMMAND *slot)
    {
        this->slot =slot;
    }
    
    void pressed ()
    {
        slot->Do();
    }      
};

class INSERTQUARTER : public COMMAND
{
    GUMBALLMACHINE *button_;
    
public:    
    INSERTQUARTER (GUMBALLMACHINE *button) : 
    button_(button)
    {}
    
    void Do ()
    {
        button_->insertQuarter();
    }
    
    void unDo ()
    {
        button_->ejectQuarter();
    }        
};

class TURNCRANK : public COMMAND
{
    GUMBALLMACHINE *button_;
    
public:    
    TURNCRANK (GUMBALLMACHINE *button) : 
    button_(button)
    {}
    
    void Do ()
    {
        button_->turnCrank();
        button_->dispense();
    }
    
    void unDo ()
    {
        button_->ejectQuarter();
    }        
};

int main()
{
    GUMBALLMACHINE *gbm =new 
    GUMBALLMACHINE (1);
    
    COMMAND *iq =new INSERTQUARTER (gbm);
    COMMAND *tc =new TURNCRANK (gbm);
    iq->Do();
    tc->Do();
    iq->unDo();
}
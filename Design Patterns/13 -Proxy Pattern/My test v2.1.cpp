#include <iostream>
#include <conio.h>


class STATE
{
protected:    
    std::string name;
    
public:
//Requestes    
    virtual void insertQuarter () =0;
    virtual void ejectQuarter () =0;
    virtual void turnCrank () =0;
    virtual void dispense () =0;
    void setName (std::string name)
    {
        this->name =name;
    }
    
    std::string getName ()
    {
        return name;
    }    
};

class REMOTE
{
public:    
    virtual int getCounter () =0;
    virtual std::string getLocation () =0;
    virtual STATE* getState () =0;
};

class GUMBALLMACHINE : public REMOTE//Real subject
{
    class STATE *soldOutState;
    class STATE *noQuarterState;
    class STATE *hasQuarterState;
    class STATE *soldState;
    
    class STATE *state =soldOutState;
    int count_ =0;
    std::string location;
    
    
public: 
    GUMBALLMACHINE (std::string location,int count);
    
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
        sleep (2);
        return count_;
    }
    
    std::string getLocation ()
    {
        sleep (2);
        return location;
    }
    
    STATE* getState ()
    {
        sleep (2);
        return state;
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
    {this->setName("Soldout\n"); }
    
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
    {this->setName("Waiting for a Quarter \n"); }
    
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
    {this->setName("Has a Quarter\n"); }
    
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
    {this->setName("Sold\n"); }
    
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

GUMBALLMACHINE::GUMBALLMACHINE 
(std::string location,int count) 
{
    this->count_ =count;
    this->location =location;
    
    soldOutState =new SO_STATE(this );
    noQuarterState =new NQ_STATE(this );
    hasQuarterState =new HQ_STATE(this );
    soldState =new S_STATE(this );
    
    if (count_ >0)
        state =noQuarterState;
}

class GBM_REMOTE : public REMOTE //proxy
{
    GUMBALLMACHINE* gbm_ ;
    
public:
    GBM_REMOTE 
    (std::string location,int count) 
    {
        this->gbm_ =new GUMBALLMACHINE 
        (location,count);
    }
    
    int getCounter ()
    {
        return gbm_->getCounter();
    } 
    
    std::string getLocation ()
    {
        return gbm_->getLocation();
    } 
    
    STATE* getState ()
    {
        return gbm_->getState();
    }   
};

class GUMBALLMONITOR
{
    REMOTE *gbm_;
public:    
    GUMBALLMONITOR (REMOTE *gbm)
    : gbm_(gbm)
    {}
    
    void report ()
    {
        std::cout<<"Gumball Machine: " + 
        gbm_->getLocation() + "\n";
        
        std::cout<<"Current Inventory: " + 
        std::to_string 
        (gbm_->getCounter()) + " Gumballs\n";
        
        std::cout<<"Current State: " + 
        gbm_->getState()->getName() + "\n";
    }    
};

int main()
{
    
    REMOTE *gbm =new GBM_REMOTE 
    ("City Centre",5);
    
    GUMBALLMONITOR *gm =new GUMBALLMONITOR 
    (gbm);
    gm->report();
}
#include <iostream>
#include <string>
#include <conio.h>

class FAN //Receiver
{
private:    
    int speed;
    std::string place_;

public:                
    FAN (std::string place) : place_(place)
    { this->speed =0; }
    
    void speedUp ()
    {
        if (speed !=4)        
        this->speed++;
        std::cout<<"Turn Speed UP Fan in " + 
        place_ + " to " + 
        std::to_string(speed)+"\n";
    }
    
     void speedDown ()
    {
        if (speed !=0)
        this->speed--;
        std::cout<<"Turn Speed DOWN Fan in " 
        + place_ + " to " +         
        std::to_string(this->speed)+"\n";
    }
};

class LIGHT //Receiver
{
private:    
    std::string place_;
    
public:    
    LIGHT (std::string place) : place_(place) 
    {}
    
    void lightON ()
    {
        std::cout<<"Turn ON Light in " + 
        place_+"\n";
    }
    
    void lightOFF ()
    {
        std::cout<<"Turn OFF Light in " + 
        place_+"\n";
    }
};

class COMMAND
{
public:    
    virtual void Do () =0;
    virtual void unDo () =0;
};

class NON : public COMMAND
{
public:
      
    void Do () 
    {}
    
    void unDo ()
    {}
};

class REMOTE //Invocer
{
private:    
    COMMAND *ON_UPslot[2];
    COMMAND *OFF_DOWNslot[2];
    COMMAND *partySlot;
    COMMAND *lastDone;//it could be stack
public:

    REMOTE () 
    {
        for (int i =0;i < 2;i++)
        {
            ON_UPslot[i] =new NON();
            OFF_DOWNslot[i] =new NON();
        }
    }     
    
    void setSlot (int index,COMMAND* ON,COMMAND* OFF)
    {
        this->ON_UPslot[index] =ON;
        this->OFF_DOWNslot[index] =OFF;         
    }
    
    void setPartySlot (COMMAND *collection)
    {
        this->partySlot =collection;
    }
       
    void pressONorUP (int index)
    {
        ON_UPslot[index]->Do();
        lastDone =ON_UPslot[index];
    }
    
    void pressOFForDOWN (int index)
    {
        OFF_DOWNslot[index]->Do();
        lastDone =OFF_DOWNslot[index];
    }
    
    void undoButton ()
    {
        std::cout<<"Re";
        lastDone->unDo();        
    }
    
    void pressPartyModeButton()
    {
        partySlot->Do();
        lastDone =partySlot;
    }
    
    void undoButtonForPartyMode ()
    {
        //std::cout<<"Re";
        lastDone->unDo();        
    }
};

class LIGHTSON : public COMMAND
{
private:    
    LIGHT* button_;

public:        
    LIGHTSON (LIGHT* button) : button_(button)
    {}
    
    void Do ()
    {
        button_->lightON();
    }
    
    void unDo ()
    {
        button_->lightOFF();
    }
};

class LIGHTSOFF : public COMMAND
{
private:    
    LIGHT* button_;

public:        
    LIGHTSOFF (LIGHT* button) : 
    button_(button)
    {}
    
    void Do ()
    {
        button_->lightOFF();
    }
    
    void unDo ()
    {
        button_->lightON();
    }
};

class FANUP : public COMMAND
{
private:    
    FAN* bobbin_;
    
public:    
    FANUP (FAN* bobbin) : bobbin_(bobbin)
    {}
    
    void Do ()
    {
        bobbin_->speedUp();
    } 
    
    void unDo ()
    {
        bobbin_->speedDown();
    }                              
};

class FANDOWN : public COMMAND
{
private:    
    FAN* bobbin_;
    
public:    
    FANDOWN (FAN* bobbin) : bobbin_(bobbin)
    {}
    
    void Do ()
    {
        bobbin_->speedDown();
    } 
    
    void unDo ()
    {
        bobbin_->speedUp();
    }                              
};

class PARTYMODE : public COMMAND//Macro Command
{
private:    
    COMMAND *collection_[2];
public:    
    PARTYMODE(COMMAND *collection[])
    {
        for (int i =0;i < 2;i++)
            collection_[i]=collection[i];
    }
    
    void Do()
    {
        for (int i =0;i < 2;i++)        
            collection_[i]->Do();
        
    }
    void unDo()
    {
        for (int i =1;i >=0;i--)
        { 
            std::cout<<"Re"; 
            collection_[i]->unDo();
        }        
    }
};


int main ()
{
    LIGHT *L1 =new LIGHT("Room");
    FAN *F1 =new FAN("Room");
    
    COMMAND* ON =new LIGHTSON(L1);
    COMMAND* OFF =new LIGHTSOFF(L1);
    
    COMMAND* UP =new FANUP(F1);
    COMMAND* DOWN =new FANDOWN(F1);
    
    REMOTE* R1 =new REMOTE();
    R1->setSlot(0,ON,OFF);
    R1->setSlot(1,UP,DOWN);
        
    R1->pressONorUP(0);
    R1->pressOFForDOWN(0);
    
    R1->undoButton();
    
    R1->pressONorUP(1);
    R1->pressONorUP(1);
    R1->pressONorUP(1);
    R1->pressONorUP(1);
    
    R1->undoButton();

    R1->pressOFForDOWN(1);
    
    COMMAND *pc[] ={new LIGHTSON(L1),new 
    FANUP(F1)};
    COMMAND *p =new PARTYMODE(pc);
    
    R1->setPartySlot(p);
    R1->pressPartyModeButton();
    R1->undoButtonForPartyMode();
        
    
 
}
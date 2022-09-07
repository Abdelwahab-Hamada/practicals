#include <iostream>
#include <string>
#include <conio.h>
//#include <vector>

class FAN
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

class LIGHT
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

class REMOTE
{
private:    
    COMMAND *ONslot[2];
    COMMAND *OFFslot[2];
    
public:

    REMOTE () 
    {
         for (int i =0;i < 2;i++)
        {
            ONslot[i] =new NON();
            OFFslot[i] =new NON();
        }
    }     
    
    void setSlot (int index,COMMAND* ON,COMMAND* OFF)
    {
        this->ONslot[index] =ON;
        this->OFFslot[index] =OFF;         
    }
       
    void pressONorUP (int index)
    {
        ONslot[index]->Do();
    }
    
    void pressOFForDOWN (int index)
    {
        OFFslot[index]->Do();
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
    
    bool again =false;
    do
    {
        clrscr();
        std::string Remote;
        char D; 
        int DB; 
        int DB2;      
        std::cout<<"Which Remote (L/F)\n";
        std::cin>>D;
        Remote =(D =='L') ? "Light":"Fan";
        
        std::cout<<Remote+" Remote\n";
        
        DB =(D == 'L') ? 0:1;
        
        if (DB == 0)
        std::cout<<"Turn ON/OFF (n/f)\n";
        else if (DB == 1)
        std::cout<<"Turn UP/DOWN (u/d)\n";
        std::cin>>D;
        
        DB2 =(D == 'n' || D == 'u') ? 0:1;
        if (DB2 == 0)
        R1->pressONorUP(DB);
        else
        R1->pressOFForDOWN(DB);
        std::cout<<"Enter To restart (1/0)"; 
       
        std::cin>>again;       
     } while (again);  
        
        
    
    
    
    
    return 0;
 
}
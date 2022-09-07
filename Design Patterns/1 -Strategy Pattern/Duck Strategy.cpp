#include <iostream>
#include <string>

using namespace std;

//.:(Fly Behaviour
class flyable //abstract supertype
{
    public:
    string virtual fly() =0;    
};
//concert implementation
class Fly : public flyable//fly With Wings 
{
    public:
    string fly()
    {
        return "I Can fly 🤪";
    }
};

class noFly : public flyable//no way to fly
{
    string fly()
    {
        return "I Can't Fly 😭";
    }
};
//Fly Behaviour):.

//.:(Duck Encapsulation
class DUCK//🦆
{
    private:
    int num;//No. of 🦆's
    string name;//Name of the 🦆 
    static int counter;//counter of 🦆's
    protected:
    flyable *FB;//(Fly Behaviour) for this 🦆
    public:
    DUCK()
    {
        this->num =++counter;
        this->name =string("Duck No.") + to_string(this->num);
        this->FB =new Fly();
    }
    
    string swimmable()
    {
        return "I Can Swim :)";
    }
    
    void perform()
    {
        cout<<"🦆"<<endl;
        cout<<this->name<<endl;
        cout<<this->display()<<endl;
        cout<<this->swimmable()<<endl;        
        cout<<this->FB->fly()<<endl;      
    }
  
    string virtual display() =0;
    
    ~DUCK()
    {
        delete FB;
    }
};

int DUCK::counter =0;
//Duck Encapsulation):.

class redHead : public DUCK
{
    public:
    string display ()
    {
        return "I'm Red Head Duck";
    }
    
    void gotShot()
    {
        this->FB =new noFly();
        cout<<"Got Shot now "<<FB->fly()<<endl;
    }
};

class yellowToy : public DUCK
{
    public:
    yellowToy()
    {
        delete FB;
        this->FB =new noFly();
    }
    string display ()
    {
        return "I'm Yellow Duck Toy";
    }    
};



int main()
{
     DUCK*D1 =new yellowToy(); 
     D1->perform();  
     DUCK*D2 =new redHead();
     D2->perform();
     ((redHead*)D2)->gotShot();
     
    
    system ("pause");
}
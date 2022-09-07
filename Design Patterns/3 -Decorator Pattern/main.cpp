#include <string>
using namespace std;

class Component
{
public:    
    void methodA () =0;
    string methodB () =0;
    
};

class ConcreteComponent : public Component
{
public:    
    void methodA ()
    {        
    }
    
    string methodB () 
    {
    }
    
};

class Decorator : public Component
{    
};

class ConcreteDecorator1 : Decorator
{
public:   
     void methodA ()
     {
     }
     
     string methodB ()
     {
     } 
     
     void newBehaviour ()
     {
     }
     
private: 
     Component*wrappedObj;
};

class ConcreteDecorator2 : Decorator
{
public:   
     void methodA ()
     {
     }
     string methodB ()
     {
     } 
     
private:

     Component*wrappedObj;     
     Object newState;   
};
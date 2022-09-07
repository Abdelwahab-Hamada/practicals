//with lazy initialization you can call a static something without use constructor or getInstance() function 
#include <iostream>
#include <thread>
#include <conio.h>
#include <chrono>
class singleton
{
public:    
    static singleton *getInstance ()
    {
        if (!unique)
            unique =new singleton;
        return unique;
    }
    int static getx()
    {
        return x_;
    }
               
private:    
     
    singleton () 
    {
        std::cout<<"Lazy Constructor()\n";
    }
   /* ~singleton () 
    {
        //delete unique;
        std::cout<<"~Lazy Destructor()\n";
    }*/
    static singleton *unique;
    static int x_;
};
int singleton::x_=12;
singleton* singleton::unique =0;

void doWork ()
{
    using namespace    
    std::literals::chrono_literals;
    singleton *s =singleton::getInstance();
    std::cout<<"Pointer :"<<&s<<std::endl;
    std::this_thread::sleep_for(.5s);   
}

int main()
{   
    //std::cout<<"main:"<<singleton::getx()<<std::endl;//outputs just main:12 without Lazy Constructor 
    //singleton::getInstance();//then Constructor
    int c;
    for (c =0;c < 100;c++)
    {
    std::thread worker (doWork);    
    worker.join();
    }
 
}
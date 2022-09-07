#include <iostream>
#include <string>
#include <list>
using namespace std;
class Pizza
{
protected:    
    string type,dough,sauce;//pizza name
    list<string>*toppings =new list<string>();
        
public:    
    string getType()
    {
        return type;
    }
    
    string prepare()
    {
        return type+" bePrepare...\n"+"Prepared";
    }
    
    string bake()
    {
        return type+" beBake...\n"+"Baked";
    }
    
    string cut()
    {
        return type+" beCut...\n"+"Cutted";
    }
    
    string box()
    {
        return type+" beBox...\n"+"Boxed";
    }
    
    void objectification ()
    {
        std::cout<<"____Pizza____"
        std::cout<<"Type :"<<type<<endl;
        std::cout<<"Dough :"<<dough<<endl;
        std::cout<<"Sauce :"<<sauce<<endl;
        for (auto it : toppings)
        std::cout<<"Topping :"<<it<<endl;
        std::cout<<"_____________";           
    } 
            
};
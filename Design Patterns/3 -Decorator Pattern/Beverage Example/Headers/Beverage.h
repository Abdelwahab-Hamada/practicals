#ifndef BEVERAGE_H
#define BEVERAGE_H
#include <string>
using namespace std;
class Beverage
{
protected:    
    string description;
public:
    Beverage ();    
    virtual string getDescription ();
    virtual double cost () =0; 
    virtual~Beverage ();
                
};
#endif
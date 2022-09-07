#include <iostream>

class Product
{
    
};
class Creator
{
protected:
     Product factoryMethod ()
     {
         
     }
public:     
     void anOperation ()
     {
     }      
};
class ConcreteProduct : public Product
{
};
class ConcreteCreator : Creator
{
public:    
    Product factoryMethod ()
    {
    }
};
int main ()
{
}
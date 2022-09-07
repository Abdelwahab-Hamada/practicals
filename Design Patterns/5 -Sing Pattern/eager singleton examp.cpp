//with Eager initialization can't call a static something without using constructor or getInstance() function 
#include <iostream>
class sin
{
private:    
    static int x_;
    static sin* ptr ;
    sin ()
    {
        printf("Eager Constructor()\n");
    }
    ~sin ()
    {       
        printf("Eager Destructor()\n");
    }
public:
    int static getx()
    {
        return x_;
    }
            
    static sin* getInst()
    {
        return ptr;
    }
};
int sin::x_=12;
sin* sin::ptr =new sin;
int main()
{
    std::cout<<"main:"<<sin::getx();
    //Eager Constructor() and main:12 
    sin::getInst();//then nothing because constructor already created by default      
}
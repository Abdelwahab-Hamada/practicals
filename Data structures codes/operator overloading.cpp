#include <iostream>

class B
{
    int x,y;
    
public:

    B (int x =0,int y =0)
    {
        this->x =x;
        this->y =y;
    }
    
    B operator +(B b)
    {
        B c;
        c.x =x +b.x;
        c.y =y +b.y;
        return c;
    }
    
    void print ()
    {
        std::cout<<x<<","<<y;
    }
                
};

int main()
{
    B b1(10,5); B b2(5,10); B b3;
    b3 =b1 + b2;
    b3.print();
    
    std::cout<<"\n";
    
    b3 =b1 + 10;
    b3.print();
    
    std::cout<<"\n";
    
    B b4(2,4); B b5(4,2); B b6;
    b6 =b4.operator+(b5);
    b6.print();
}
#include <iostream>
#include <vector>

class VEGETABLES
{
public:    
    virtual void plantingInBrownSoil () =0;
};

class CARROT : public VEGETABLES
{
public:    
    void plantingInBrownSoil ()
    {
        std::cout<<"Carrots Planted In Brown" 
                 <<" Soil\n";
    }
};

class TOMATOE : public VEGETABLES
{
public:    
    void plantingInBrownSoil ()
    {
        std::cout<<"Tomatoes Planted In Brown"
                 <<" Soil\n";          
    }
};

class FRUITS
{
public:    
    virtual void plantingInRedSoil () =0;
};

class APLLE : public FRUITS
{
public:    
    void plantingInRedSoil ()
    {
        std::cout<<"Apples Planted In Red"
                 <<" Soil\n";
    }
};

class FRUITSADAPTER : public VEGETABLES ,public APLLE //class adaptive
{
public:        
    void plantingInBrownSoil ()
    {
        plantingInRedSoil();
    }
};

int main()
{
    VEGETABLES *veggies [3];
    
     veggies[0] =new CARROT;
     veggies[1]=new TOMATOE;
     veggies[2] =new FRUITSADAPTER;

    for (int i =0;i<3 ;i++)
    veggies[i]->plantingInBrownSoil();
        
} 
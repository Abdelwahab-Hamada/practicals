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

class FRUITSADAPTER : public VEGETABLES
{
private:    
    FRUITS *FtoV_; //object adaptive
public:    
    FRUITSADAPTER (FRUITS *FtoV) : FtoV_(FtoV)
    {}
    void plantingInBrownSoil ()
    {
        FtoV_->plantingInRedSoil();
    }
};

int main()
{
    
    std::vector<VEGETABLES*> veggies ={new 
    CARROT,new TOMATOE};
    
    veggies.push_back(new FRUITSADAPTER (new 
    APLLE));

    for (int i =0;i<3 ;i++)
    veggies.at(i)->plantingInBrownSoil();    
} 
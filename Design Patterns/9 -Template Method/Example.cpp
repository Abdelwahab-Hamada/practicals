#include <iostream>

class HOTBEVERAGE
{
protected:    
    void boilWater ()
    {
        std::cout<<"Water has been Boiling "
                 <<"...\t\t\tDone\n";
    }
    virtual void putMainRaw () =0;
    
    void pourWater ()
    {
        std::cout<<"Water has been Pouring "
                 <<"...\t\t\tDone\n";
    }
    
    virtual void putExtras () =0;
    
    virtual bool extras ()
    {
        return true;
    }
    
    virtual void hook() {};
public:

    void prepareBeverage ()
    {
        boilWater ();
        putMainRaw ();
        pourWater ();
        hook (); 
        if (extras ())
            putExtras ();
        else    
            std::cout<<"Without Extras \n";
        
        std::cout<<"\nHot Beverage Ready to "
                 <<"be Serve\n";
    }            
};

class TEA : public HOTBEVERAGE
{
    bool extras_;
    
    void putMainRaw ()
    {
        std::cout<<"Putting Tea pack\n";
    }
    
    void putExtras ()
    {
        std::cout<<"Putting Lemon\n";
    }
    
    bool extras ()
    {
        if (extras_)
            return true;
        else 
            return false;
    }
public:    
    TEA (bool extras) : extras_(extras)
    {}
};

class COFFEE : public HOTBEVERAGE
{
    void putMainRaw ()
    {
        std::cout<<"Putting Coffee Seeds \n";
    }
    
    void putExtras ()
    {
        std::cout<<"Putting Sugar and Milk\n";
    }
    
    void hook ()
    {
        std::cout<<"I AM Hooked\n";
    }
    
};

main()
{
    HOTBEVERAGE *hbTea =new TEA ( false );
    hbTea->prepareBeverage();
    std::cout<<"\n\t-----------\n";
    HOTBEVERAGE *hbTea2 =new TEA ( true );
    hbTea2->prepareBeverage();
    std::cout<<"\n\t-----------\n";
    HOTBEVERAGE *hbCoffee =new COFFEE;
    hbCoffee->prepareBeverage();
}
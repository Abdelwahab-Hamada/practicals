#include <iostream>
#include <string>
#include <list>
#include <vector>

class MENUITEM
{
    std::string name_;
    
public:

    MENUITEM (std::string name) :name_(name)
    {        
    }    
    std::string getName ()
    {
        return name_;
    }    
};

class PCHMENU
{
    std::list<MENUITEM> menuItems;
    
public:    
    PCHMENU ()
    {
        addItem("K&B Pc");
        addItem("Regular Pc");
        addItem("Blueberry Pc");
        addItem("Waffels");
    }
    
    void addItem (std::string name)
    {
        MENUITEM *mi =new MENUITEM(name);
        menuItems.push_back(*mi);
    }
    
    std::list<MENUITEM> getMenuItems ()
    {
        return menuItems;
    }    
};

class DMENU
{
    std::vector<MENUITEM> menuItems;
    int numOfItems =0;
    
public:    
    DMENU ()
    {
        addItem("Veggie BLT");
        addItem("Beef");
        addItem("Soup");
        addItem("Hotdog");
    }
    
    void addItem (std::string name)
    {
        MENUITEM *mi =new MENUITEM(name);
        menuItems.push_back(*mi);
        numOfItems++;
    }
    
    std::vector<MENUITEM> getMenuItems ()
    {
        return menuItems;
    }    
};

class WAITRESS
{
    PCHMENU *phMenu =new PCHMENU ();
    std::list<MENUITEM> breakfastMenu =
    phMenu->getMenuItems();
    DMENU *dMenu =new DMENU ();
    std::vector<MENUITEM> lunchMenu =
    dMenu->getMenuItems();
    
public:    
    void showMenu ()
    {
        std::cout<<"Menu1:\n";
        for (auto x : breakfastMenu)
             std::cout<<x.getName()<<"\n";
        std::cout<<"--------\n";     
        std::cout<<"Menu2:\n";     
        for (int i =0;i < lunchMenu.size() ;
        i++)             
        std::cout<<lunchMenu.at(i).getName() 
            <<"\n";         
    }
};

      

int main()
{
    WAITRESS *wt =new WAITRESS;
    wt->showMenu();
}
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

class IT
{
public:    
   virtual bool hasNext() =0;
   virtual MENUITEM next () =0; 
};

class MENU 
{
public:    
    virtual IT* createIt ()=0;
};

class PCHMENU_IT : public IT
{
    std::list<MENUITEM> items;
    std::list<MENUITEM>::iterator it 
    =items.begin();
    int pos =-1;
    
public:    
    PCHMENU_IT (std::list<MENUITEM> items)
    {
        this->items =items;
    }
    
    MENUITEM next ()
    {
        MENUITEM mi =*it;
        it++;
        pos++;
        return mi;
    }
    
    bool hasNext ()
    {
        if (pos == items.size())
        return false;
        else
        return true;
    }
};

class DMENU_IT : public IT
{
    std::vector<MENUITEM> items;
    int pos =0;
    
public:    
    DMENU_IT (std::vector<MENUITEM> items)
    {
        this->items =items;
    }
    
    MENUITEM next ()
    {
        MENUITEM mi =items.at(pos);
        pos++;
        return mi;
    }
    
    bool hasNext ()
    {
        if (pos >= items.size())
        return false;
        else
        return true;
    }
};

class PCHMENU : public MENU
{
    std::list<MENUITEM> menuItems;
    
public:    
    PCHMENU ()
    {
        addItem("K&B Pc\n");
        addItem("Regular Pc\n");
        addItem("Blueberry Pc\n");
        addItem("Waffels\n");
    }
    
    void addItem (std::string name)
    {
        MENUITEM *mi =new MENUITEM(name);
        menuItems.push_back(*mi);
    }
    
    IT* createIt ()
    {
        return new PCHMENU_IT(menuItems) ;
    }    
};

class DMENU : public MENU
{
    std::vector<MENUITEM> menuItems;
    
    
public:    
    DMENU ()
    {
        addItem("Veggie BLT\n");
        addItem("Beef\n");
        addItem("Soup\n");
        addItem("Hotdog\n");
    }
    
    void addItem (std::string name)
    {
        MENUITEM *mi =new MENUITEM(name);
        menuItems.push_back(*mi);
    }
    
    IT* createIt ()
    {
        return new DMENU_IT(menuItems);
    }    
};

class WAITRESS
{
    MENU *phMenu;   
    MENU *dMenu;
        
public:
    WAITRESS (MENU *phMenu,MENU *dMenu)
    {
       this->phMenu =phMenu;
        this->dMenu =dMenu;
        
    }
    
    void printMenu ()
    {
        IT *pIt =phMenu->createIt();
        IT *dIt =dMenu->createIt();
        
        std::cout<<"Menu\n----\nBreakfast:\n";
        printMenu (pIt);
        std::cout<<"\nLunch:\n";
        printMenu (dIt);
    }
    
    void printMenu (IT *it)
    {
        while (it->hasNext())
        {
            MENUITEM mi =it->next();
            std::cout<<mi.getName();
        }
    }   
};

      

int main()
{
    MENU *m1 =new PCHMENU ();
    MENU *m2 =new DMENU ();
    
    WAITRESS *w =new WAITRESS (m1,m2);
    w->printMenu();    
}
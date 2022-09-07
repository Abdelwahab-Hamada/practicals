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

class PCHMENU
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

class DMENU
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
    PCHMENU phMenu;
    
    //std::list<MENUITEM> breakfastMenu =
    //phMenu->getMenuItems();
    //std::list<MENUITEM>::iterator it =
    //breakfastMenu.begin();
    
    DMENU dMenu;
    
    //std::vector<MENUITEM> lunchMenu =
    //dMenu->getMenuItems();
    
public:
    WAITRESS (PCHMENU phMenu,DMENU dMenu)
    {
        this->phMenu =phMenu;
        this->dMenu =dMenu;
        
    }
    
    void printMenu ()
    {
        IT *pIt =phMenu.createIt();
        IT *dIt =dMenu.createIt();
        
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
        
    /*void showMenu ()
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
    
    void printMenu ()
    {
        for (int i =0; i < 
        breakfastMenu.size();i++)
        {
        MENUITEM mi 
        =*it;        
        it++;
        std::cout<<mi.getName()<<std::endl;
        }
        
        for (int i =0; i < 
        lunchMenu.size();i++)
        {
        MENUITEM mi =lunchMenu.at(i);
        std::cout<<mi.getName()<<std::endl;
        }
               
    }*/
};

      

int main()
{
    PCHMENU *m1 =new PCHMENU ();
    DMENU *m2 =new DMENU ();
    
    WAITRESS *w =new WAITRESS (*m1,*m2);
    w->printMenu();
    /*WAITRESS *wt =new WAITRESS;
    wt->showMenu();
    std::cout<<"-------\nMerged Menu :\n\n";
    wt->printMenu();*/
}
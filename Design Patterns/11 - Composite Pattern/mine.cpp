#include <iostream>
#include <string>
#include <list>
#include <vector>

class MENUCOMPO //component
{
public:    
    virtual void  add(MENUCOMPO* )
    {
    }
    
    //virtual MENUCOMPO* getChild (int i);
    
    virtual std::string getName () =0;
    
    virtual void print () =0;
    
    virtual ~MENUCOMPO () {}
};

class MENUITEM : public MENUCOMPO //leaf
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
    
    void print ()
    {
        std::cout<<"\n\t" + this->getName() 
                   + "\n"; 
    }   
};

class MENU : public MENUCOMPO //composite
{
    std::vector<MENUCOMPO*> mc;
    std::string name_;
    std::string meal;
    static int counter;
    int num;

public:
    MENU (std::string name,std::string meal) 
    : name_(name)
    {
        this->meal =meal;
        this->num =++counter;
    }
    
    void add (MENUCOMPO* menuCompo)
    {
        mc.push_back(menuCompo);
    }
    
    std::string getName ()
    {
        return name_;
    }
    
    std::string getMeal ()
    {
        return meal;
    }
    
    void print ()
    {
        std::cout<<"(" + std::to_string(num) + "){" 
        + this->getName() + 
        "," + getMeal() +
        "\n\t---------\n";
                   
        for (auto * it : mc)
             it->print();
             
        std::cout<<"\n}(" + 
        std::to_string(num) + ")";                             
    }
    
    ~MENU () {}
};

int MENU::counter =0;

class WAITRESS
{    
    MENUCOMPO* allMenus;
    
public:        
    WAITRESS (MENUCOMPO * allMenus)
    {
        this->allMenus =allMenus;
    }
    
    void printMenu ()
    {
        allMenus->print();
    }
};

      

int main()
{
     MENUCOMPO* PCH_menu =new MENU 
     ("Pancakes House Menu","Breakfast");
     MENUCOMPO* D_menu =new MENU 
     ("Diner House Menu","lunch");
     MENUCOMPO* C_menu =new MENU 
     ("Café Menu","Dinner");
     MENUCOMPO* dessert_menu =new MENU 
     ("Dessert Menu","Today's Desserts"); 
     
     MENUCOMPO* allMenus =new MENU 
     ("   All Menus","Combined");
     
     allMenus->add(PCH_menu);
     allMenus->add(D_menu);
     allMenus->add(C_menu);
     
     D_menu->add(new MENUITEM ("Pasta"));
     D_menu->add(dessert_menu);
     
     dessert_menu->add(new MENUITEM                                   ("Apple Pie"));
     
     PCH_menu->add(new MENUITEM
                  ("Toast and Cheese"));
     
     C_menu->add(new MENUITEM ("Lemonade"));
     
     WAITRESS* w =new WAITRESS (allMenus);
     w->printMenu();
                                                                     
}
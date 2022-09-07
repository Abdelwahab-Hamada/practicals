#include <vector>
#include <list>
#include <string>
#include <iostream>
class OBJ;

class IT
{
public:    
   virtual bool hasNext() =0;
   virtual OBJ *next (); 
};

class LIST_IT : public IT
{    
    std::list<OBJ*> myL;
    std::list<OBJ*>::iterator x 
    =myL.begin();
public:  
    LIST_IT (std::list<OBJ*> L)
    {
        myL =L;
    }
    bool hasNext ()
    {
        if (x == myL.end())
            return false;
        else
            return true;
    }
    
    OBJ *next ()
    {
        
        OBJ *temp =*x;
        x++;
        return temp;
    }    
};

class ARRAY_IT : public IT
{
    std::vector<OBJ*> myA;
    int pos =0;
public:    
    ARRAY_IT (std::vector<OBJ*> Array)
    {
        myA =Array;
    }
    bool hasNext ()
    {
        if (pos >=myA.size())
            return false;
        else
            return true;
    }
    
    OBJ *next ()
    {
        OBJ *temp =myA.at(pos);
        pos++;
        return temp;
    }
};

class RESLIST
{
private:    
    std::list<std::string> menu;
   
public:
    RESLIST ()
    {
        menu.push_back("Margretta");
        menu.push_back("Mix Cheese");
        menu.push_back("Barbekeo");
    }
    std::list<std::string> getMenu()
    {
        return menu;
    }
};

class RESARRAY
{
private:    
    std::vector<std::string> menu;
   
public:
    RESARRAY ()
    {
        menu.push_back("Bebroni");
        menu.push_back("Clam");
        menu.push_back("Sea Food");
    }
    std::vector<std::string> getMenu()
    {
        return menu;
    }
};

class WAITRESS
{
    RESLIST *L_;
    RESARRAY *A_;
public:    
    WAITRESS (RESLIST *L,RESARRAY *A)
    {
        L_=L;
        A_=A;
    }
    void showMenu ()
    {
        std::list<std::string> menu1 
        =L_->getMenu();
        std::vector<std::string> menu2
        =A_->getMenu();
        
        std::cout<<"Menu1:\n";
        for (auto x : menu1)
             std::cout<<x<<"\n";
        std::cout<<"--------\n";     
        std::cout<<"Menu2:\n";     
        for (int i =0;i < menu2.size() ;i++)             std::cout<<menu2.at(i) 
            <<"\n";           
    }
};
int main()
{
    RESLIST *r1 =new RESLIST();
    RESARRAY *r2 =new RESARRAY();
    WAITRESS *wt =new WAITRESS (r1,r2);
    wt->showMenu();
    
    return 0;
    
}
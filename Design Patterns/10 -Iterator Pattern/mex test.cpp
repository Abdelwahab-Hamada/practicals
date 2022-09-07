#include <vector>
#include <list>
#include <string>
#include <iostream>

template<typename OBJ>
class IT
{
public:    
   virtual bool hasNext() =0;
   virtual OBJ next (); 
};

template<typename OBJ>
class LIST_IT : public IT<OBJ>
{
    
public:    
    std::list<OBJ> myL;
    typename
    std::list<OBJ>::iterator x 
    =myL.begin();
  
    LIST_IT (std::list<OBJ> L)
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
    
    OBJ  next ()
    {
        OBJ temp =x;
        x++;
        return temp;
    }    
};

template<typename OBJ>
class ARRAY_IT : public IT<OBJ>
{    
public:    
    std::vector<OBJ> myA;
    int pos =0;    
   
    ARRAY_IT (std::vector<OBJ> Array)
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
    
    OBJ next ()
    {
        OBJ temp =myA.at(pos);
        pos++;
        return temp;
    }
};
template<typename OBJ>
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
    IT<OBJ> *getIt()
    {
        return new LIST_IT<OBJ>(menu);
        
    }
};
template<typename OBJ>
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
    IT<OBJ> *getIt()
    {
        return new ARRAY_IT<OBJ>(menu);
    }
};
template<typename OBJ>
class WAITRESS
{
    RESLIST<OBJ> *L_;
    RESARRAY<OBJ> *A_;
public:    
    WAITRESS (RESLIST<OBJ> 
    *L,RESARRAY<OBJ> 
    *A)
    {
        L_=L;
        A_=A;
    }
    
    void showMenu ()
    {
        IT<OBJ> *rl =L_->getIt();
        IT<OBJ> *ra =A_->getIt();
        
        showMenu(rl); 
        showMenu(ra);                 
    }
    
    void showMenu (IT<OBJ> *i)
    {
        while (i->hasNext())
        {
            std::cout<<i->next();
        }
    }
};
int main()
{
    RESLIST<std::string> *r1 =new 
    RESLIST<std::string>;
    RESARRAY<std::string> *r2 =new 
    RESARRAY<std::string>;
    WAITRESS<std::string> *wt 
    =new WAITRESS<std::string>(r1,r2);
    wt->showMenu();
    
    return 0;
    
}
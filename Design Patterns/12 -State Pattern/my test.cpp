#include <iostream>

class GUMBALLMACHINE
{
   enum machineStates     
   {soldOut,noQuarter,hasQuarter,sold};

   int state =soldOut;
   int count_ =0;
   
public:   
   GUMBALLMACHINE (int count) : count_(count)
   {
       if (count_ > 0)
           state =noQuarter;
       std::cout<<"Gumballs Machine 2004\n";
       std::cout<<"Inventory : (" <<count
       <<") Gumballs\n\n";
       std::cout<<"Machine Waiting for "
                <<"Quarter\n\n";
   }
   
   void insertQuarter ()
   {
       if (state == hasQuarter)
           std::cout<<"You can't insert "
                    <<"another Quarter\n"; 
                     
       else if (state == noQuarter)
       {
                state =hasQuarter;
                std::cout<<"You inserted a "
                         <<"Quarter\n";
       }                   
                          
       else if (state == soldOut)
                std::cout<<"Gumballs Soldout"
                         <<",Quarter "
                         <<"Ejected\n"; 
                          
       else if (state == sold)
                std::cout<<"Please Wait ,"
                         <<"Gumball on "
                         <<"the Way\n";  
   }
   
   void ejectQuarter ()
   {
       if (state == hasQuarter)
       {
           std::cout<<"Quarter Returned\n";
           state =noQuarter;
       } 
           
       else if (state == noQuarter)
                std::cout<<"You haven't "
                         <<"inserted a "
                         <<"Quarter\n"; 
                                
       else if (state == sold)
                std::cout<<"Sorry ,you turned"
                         <<"the Crank \n"; 
                          
       else if (state == soldOut)
                std::cout<<"Can't Eject"
                         <<",you haven't "
                         <<"inserted a "
                         <<"Quarter yet\n";
   }
   
   void turnCrank ()
   {
       if (state == sold)
           std:: cout<<"Turning Twice "
                     <<"doesn't get you "
                     <<"another Gumball\n"; 
                      
       else if (state == noQuarter)
                std::cout<<"You turned ,"
                         <<"but there's "
                         <<"no Quarter\n"; 
                           
       else if (state == soldOut)
                std::cout<<"You turned ,"
                         <<"but there's "
                         <<"no Gumballs\n"; 
                           
       else if (state == hasQuarter)
       {
                std::cout<<"You turned...\n";
                state = sold;
                dispense ();
       }              
   }
   
   void dispense ()
   {
       if (state == sold)
       {
           std::cout<<"A Gumball comes "
                    <<"rolling out the"
                    <<"Slot\n";
           count_--;
           if (count_ == 0)
           {
               std::cout<<"Oops ,Out of "
                        <<"Gumballs\n";
               state =soldOut;
           }else
               state =noQuarter;
       } 
       
       else if (state == noQuarter)
                std::cout<<"You need to "
                         <<"pay first\n"; 
                          
       else if (state == soldOut)
                std::cout<<"No Gumball "
                         <<"dispensed\n";
       else if (state == hasQuarter)
                std::cout<<"No Gumball "
                         <<"dispensed\n";        }      
};

int main ()
{
    GUMBALLMACHINE *gbm =new 
    GUMBALLMACHINE (5);
    
    std::cout<<"\n_________Gumballs "
             <<"Machine__________\n\n";
    
    gbm->insertQuarter();
    gbm->turnCrank();
    
    std::cout<<"__________________"
             <<"_________________\n\n";
    
    std::cout<<"_________Gumballs "
             <<"Machine__________\n\n";
    
    gbm->insertQuarter();
    gbm->ejectQuarter();
    gbm->turnCrank();
    
    std::cout<<"__________________"
             <<"_________________\n\n";
             
    std::cout<<"_________Gumballs "
             <<"Machine__________\n\n";
             
    gbm->insertQuarter();
    gbm->turnCrank();
    gbm->insertQuarter();
    gbm->turnCrank();
    gbm->ejectQuarter();
    
    std::cout<<"__________________"
             <<"_________________\n\n";
             
    std::cout<<"_________Gumballs "
             <<"Machine__________\n\n";
    
    gbm->insertQuarter();
    gbm->insertQuarter();
    gbm->turnCrank();
    gbm->insertQuarter();
    gbm->turnCrank();
    gbm->insertQuarter();
    gbm->turnCrank();
                          
    std::cout<<"__________________"
             <<"_________________\n\n";        
                    
    return 0;
}
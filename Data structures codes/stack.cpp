#include <iostream>
using namespace std;
#define size 4

class stack{
    int Arr[size];
    int top =-1;    
public :
void pushArr(int value)
{
   if (top == size-1)
        printf("\nStack is full");
   else
   {
   top++;
   Arr[top] =value;
   printf("\nInsertation success"); 
   }       
}
void popArr()
{
    if (top == -1)
         printf("\nStack is empty");
    else
    {
        printf("\nDeleted : %d",Arr[top]);
        top--;
    }
}
void displayArr()
{
    if (top == -1)
         printf("\nStack is empty");
    else
    {
        printf("\nStack elements are : \n");
        for(int i=top; i>=0;i--)
              printf("%d\n",Arr[i]);
    }    
}





};
main()
{
    stack A;
    A.pushArr(5);
    A.pushArr(4);
    A.pushArr(3);
    A.pushArr(2);
    A.popArr();
    A.pushArr(1);
    A.popArr();
    A.displayArr();
    
    
    
    
    
    
    
}
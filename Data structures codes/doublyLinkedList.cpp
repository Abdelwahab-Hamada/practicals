#include <iostream>
using namespace std;
class doublyLinkedList {
	struct Hold
	{
		int dF;
		Hold*nexLF;
		Hold*preLF;
	};
	Hold*head;
	Hold*tail;
	int legnth;
public:
     doublyLinkedList()
     {
     	head =tail =NULL;
     	legnth =0;
     }
     //empty Set Of Nodes
bool emptySONs()
{
     	return legnth == 0;
}
     //Insert a Node & Data in Front
void pushHead(int data)
{
    Hold*hotNode =new Hold;
    hotNode->dF =data;
    if (emptySONs())
    {
         head =tail =hotNode;
         hotNode->nexLF =hotNode->preLF =NULL;
    }else
           {
               hotNode->nexLF =head;
               hotNode->preLF =NULL;
               head->preLF =hotNode;
               head =hotNode;
           }
           legnth++;
}
      //Delete Node From Front
void popHead()
{
         if (emptySONs())
             cout<<"\n\n\nNodes :- (Empty!!!)"<<"\t\t\t\t-no NODE in Front to be deleted";
         else if (legnth == 1)
         {
                      cout<<"\n\n\nFirst NODE Deleted with it's DATA("<<head->dF<<").";
                      delete head;
                       tail =head =NULL;
                       legnth--;
           
         }else 
                  {
                      Hold*targetedNode=head;
                      //1-make the 1st node is the 2nd node
                      head =head->nexLF;
                      cout<<"\n\n\nDeleted Data : ("<<targetedNode->dF<<")"<<"\t\t\t\t-from Front";
                      head->preLF =NULL;
                      //2-deleting the old 1st
                      delete targetedNode;
                      legnth--;
                  }
}
      //Insert a Node & Data in End
void pushTail(int data)
{
    Hold*hotNode =new Hold;
    hotNode->dF =data;
    if (emptySONs())
    {
         tail =head =hotNode;
         hotNode->nexLF =hotNode->preLF =NULL;
    }else
           {
               hotNode->nexLF =NULL;
               hotNode->preLF =tail;
               tail->nexLF =hotNode;
               tail =hotNode;               
           }
           legnth++;
}
//Delete Node From End
void popTail()
{
         if (emptySONs())
             cout<<"\n\n\nNodes :- (Empty!!!)"<<"\t\t\t\t-no NODE in End to be deleted";
         else if (legnth == 1)
            {
                      cout<<"\n\nLast NODE Deleted with it's DATA("<<head->dF<<").";
                      delete tail;
                      head =tail =NULL;
                      legnth--;
            }else 
                  {
                       Hold*targetedNode =tail;
                       tail =targetedNode->preLF;
                       tail->nexLF =NULL;                                              
                           cout<<"\n\n\nDeleted Data : ("<<targetedNode->dF<<")"<<"\t\t\t\t-from End"; 
                           delete targetedNode;                           
                           //1-make the previous node is the last node
                           legnth--;                     
                  }
}
      //Insert a Node & Data in Position
void pushAtPos(int pos,int data)
{
    while (pos < 0 || pos >=legnth && legnth != 0)
              {                        
                     cout<<"\n\n\nERROR"<<" Re-enter Position to imsert Data : ";
                     cin>>pos;
                         
              }
          Hold*hotNode =new Hold;
      	hotNode->dF =data;
      	if (emptySONs())
      	     pos =0;
      	if (pos == 0)
          	pushHead(data);
      	else if (pos == legnth)
                   	pushTail(data);
      	else
      	{
      	    //Algorithm to preTarget a node
      	   	Hold*preTargetedNode =head;
         		for (int h =1; h <pos ;h++)
          		{
         		   	preTargetedNode =preTargetedNode->nexLF;
          		}
          		//1-Linking new node with the right node 
         		hotNode->nexLF =preTargetedNode->nexLF;
         		hotNode->preLF =preTargetedNode;
         		//2-Linking previous node with the new node
         		preTargetedNode->nexLF =hotNode;
         		preTargetedNode->nexLF->preLF =hotNode;
         		legnth++;
      	}
      	    
    
}

     // Display All Nodes
void print()
{
      	Hold*targetedNode =head;
      	if (emptySONs())
         	cout<<"\n\n\nNodes :- (Empty!!!)"<<"\t\t\t\t-There is no DATA to print";
      	else if (! emptySONs())
      	{
                  	cout<<"\n\n\nNodes :-";
        	while (targetedNode != NULL)
          	{
              		cout<<" ("<< targetedNode->dF <<") ";
              		targetedNode =targetedNode->nexLF;
          	}
      	}           	
}
    
    


};
main ()
{
    doublyLinkedList A;
    A.pushHead(10);
    A.pushTail(30);
    A.pushAtPos(1,20);
    A.print();
    A.popHead();
    A.popTail();
    
    
    
    
    
    
    
    
}
               
    
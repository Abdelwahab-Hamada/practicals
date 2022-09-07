#include <iostream>
using namespace std;
class linkedList {
	struct Hold
	{
		int dF;
		Hold*lF;
	};
	Hold*head;
	Hold*tail;
	int legnth;
public:
     linkedList()
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
    //create a new node with data in dF
     	Hold*hotNode=new Hold;
     	hotNode->dF =data;
     	//if it's the 1st node
     	if (legnth == 0)
     	{
     		head=tail=hotNode;
     		hotNode->lF =NULL;
     	}
     	//if it's not the 1st node
     	else 
     	        {
     	            //1-linking the new node with the 1st node
     	        	hotNode->lF =head;
     	        	//2-now make the new node is the 1st node 
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
                      Hold*current_PTR=head;
                      //1-make the 1st node is the 2nd node
                      head =head->lF;
                      cout<<"\n\n\nDeleted Data : ("<<current_PTR->dF<<")"<<"\t\t\t\t-from Front";
                      //2-deleting the old 1st
                      delete current_PTR;
                      legnth--;
                  }
}
     //Insert a Node & Data in End
void pushTail(int data)
{
     	Hold*hotNode =new Hold;
     	hotNode->dF =data;
     	if (legnth == 0)
     	{
      		head =tail =hotNode;
      		hotNode->lF =NULL;
     	}else 
     	        {
     	            //1-link the last node with new node
     	        	tail->lF =hotNode;     	        	
     	        	hotNode->lF =NULL;
     	        	//2-make the new node is the last node
     	        	tail=hotNode;
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
                       Hold*current_PTR =head->lF;
                       Hold*preCurrent_PTR =head;
                       //Algorithm to preTarget a node
                       while (current_PTR != tail)
                         {
                                  preCurrent_PTR =current_PTR;
                                  current_PTR =current_PTR->lF;
                         }
                           cout<<"\n\n\nDeleted Data : ("<<current_PTR->dF<<")"<<"\t\t\t\t-from End"; 
                           delete current_PTR;                           
                           preCurrent_PTR->lF =NULL;
                           //1-make the previous node is the last node
                           tail =preCurrent_PTR;
                           legnth--;                     
                  }
}         
     //Insert a Node & Data in Position
void pushAtPos (int pos,int data)     
{
    while (pos < 0 || pos >=legnth && legnth != 0)
              {                        
                     cout<<"\n\n\nERROR"<<" Re-enter Position to insert Data : ";
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
      	   	Hold*preCurrent_PTR =head;
         		for (int h =1; h <pos ;h++)
          		{
         		   	preCurrent_PTR =preCurrent_PTR->lF;
          		}
          		//1-Linking new node with the right node 
         		hotNode->lF =preCurrent_PTR->lF;
         		//2-Linking previous node with the new node
         		preCurrent_PTR->lF =hotNode;
         		legnth++;
      	}
}
      //Delete a Node from Position
void popAtPos (int pos)     
{           	 
          while (pos < 0 || pos >=legnth && legnth != 0)
              {                        
                     cout<<"\n\n\nERROR"<<" Re-enter Position to Delete : ";
                     cin>>pos;
                         
              }            
      	if (emptySONs())
          	cout<<"\n\n\nNodes :- (Empty!!!)"<<"\t\t\t\t-no Node at ["<<pos<<"] to be deleted";
      	else
      	{          	
          if (pos == 0)
      	{
          	popHead();
          	if (legnth == 0)
              	tail =NULL;
      	}    	
      	else 
        	{     	    
          	Hold*current_PTR =head->lF;
          	Hold*preCurrent_PTR =head;
          	//Algorithm to pre target a node
             for (int h =1; h <pos; h++)
       		{
        			preCurrent_PTR =current_PTR;
        			current_PTR =current_PTR->lF;
       		}
      		preCurrent_PTR->lF =current_PTR->lF;
      	    if (tail == current_PTR)
      	        tail =preCurrent_PTR;
      	    cout<<"\n\n\nDeleted Data : ("<<current_PTR->dF<<")"<<"\t\t\t\t-from ["<<pos<<"]";
      	    delete current_PTR;
      	    legnth--;
        	}
      	}          	        	     	                               	
}
// Display All Nodes
void print()
{
      	Hold*current_PTR =head;
      	if (emptySONs())
         	cout<<"\n\n\nNodes :- (Empty!!!)"<<"\t\t\t\t-There is no DATA to print";
      	else if (! emptySONs())
      	{
                  	cout<<"\n\n\nNodes :-";
        	while (current_PTR != NULL)
          	{
              		cout<<" ("<< current_PTR->dF <<") ";
              		current_PTR =current_PTR->lF;
          	}
      	}           	
}
//Search for Data
void findData (int pos)
{
          while (pos < 0 || pos >=legnth)
               {    	 
                     cout<<"\n\n\nERROR"<<" Re-enter Position to Find DATA: ";
                     cin>>pos;
           	 }           
          Hold*current_PTR=head->lF;
          Hold*preCurrent_PTR =head;
          if (pos <1)
              current_PTR =head;
          else
          {
      		for (int h =1;h <pos ;h++)
        		{
         		    preCurrent_PTR =current_PTR;
         			current_PTR =current_PTR->lF;
        		}
          }
      		if (current_PTR != NULL)  
              	cout<<"\n\n\nPosition : ["<<pos<<"]"<<"\t\t\t\t\t-DATA Found   : ("<< current_PTR->dF<< ")";
      	else
              	cout<<"\n\n\nPosition : ["<<pos<<"]"<<"\t\t\t\t\t-DATA not found";          
}
//Search for Position
void findPosition (int val)
{ 
         Hold*current_PTR=head;
         int pos =0;
         int count =0;
         cout<<"\n\n\nDATA : ("<<val<<")"<<"\t\t\t\t\t-Found in ";
      		while (current_PTR != NULL)
      		{      	        	
       	      	    if (current_PTR->dF == val)
       	      	    {
      	      	     	cout<<"["<<pos<<"]";
      	      	     	count++;
       	      	    }
             		    current_PTR =current_PTR->lF;  
             	 	   pos++;
      		}
      		if (count == 0)
      		    cout<<"NOwhere";
}
void reverseNode()
{
    Hold*preCurrent_PTR =NULL;
    Hold*current_PTR =head;
    Hold*nexcurrent_PTR =current_PTR->lF;
    while (nexcurrent_PTR != NULL || current_PTR != NULL)
    {
        //1-save the addresses of the rest nodes
               nexcurrent_PTR =current_PTR->lF;
               //2-reverse the targeted node link direction
               current_PTR->lF =preCurrent_PTR;
               //3-move the all 3 pointers
               preCurrent_PTR =current_PTR;
               current_PTR =nexcurrent_PTR;
    }
    //make the last node is the head
    head =preCurrent_PTR;
    cout<<"\n\n\nNodes Reversed";
}
        
      		             		                		           	     		        

      	
};
main()
{
	linkedList A;
	A.pushHead(10);
	A.pushTail(40);
	A.pushAtPos(1,20);
	A.pushAtPos(2,30);
	A.pushHead(00);
	A.pushTail(50);
	A.pushAtPos(1,1);
	A.findData(0);
	A.findData(100);
	A.findPosition(2000);
	A.findPosition(30);
	A.print();
	A.popHead();
	A.popTail();
	A.popAtPos(2);
	A.popAtPos(10);
	A.print();
	A.popHead();
	A.print();
	A.popTail();
	A.popHead();
	A.popTail();
	A.popAtPos(1);

	cout<<"\n\n\n\t\t\t   *(New Linked List)*";	
	linkedList B;
	B.pushHead(100);
	B.pushHead(0);
	B.pushTail(300);
	B.pushAtPos(2,200);
	B.print();
	B.reverseNode();
	B.print();
	
}
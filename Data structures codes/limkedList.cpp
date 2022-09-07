#include <iostream>
using namespace std;
class linkedList {
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
     		hotNode->nexLF =NULL;
     	}
     	//if it's not the 1st node
     	else 
     	        {
     	            //1-linking the new node with the 1st node
     	        	hotNode->nexLF =head;
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
                      Hold*targetedNode=head;
                      //1-make the 1st node is the 2nd node
                      head =head->nexLF;
                      cout<<"\n\n\nDeleted Data : ("<<targetedNode->dF<<")"<<"\t\t\t\t-from Front";
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
     	if (legnth == 0)
     	{
      		head =tail =hotNode;
      		hotNode->nexLF =NULL;
     	}else 
     	        {
     	            //1-link the last node with new node
     	        	tail->nexLF =hotNode;     	        	
     	        	hotNode->nexLF =NULL;
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
                       Hold*targetedNode =head->nexLF;
                       Hold*preTargetedNode =head;
                       //Algorithm to preTarget a node
                       while (targetedNode != tail)
                         {
                                  preTargetedNode =targetedNode;
                                  targetedNode =targetedNode->nexLF;
                         }
                           cout<<"\n\n\nDeleted Data : ("<<targetedNode->dF<<")"<<"\t\t\t\t-from End"; 
                           delete targetedNode;                           
                           preTargetedNode->nexLF =NULL;
                           //1-make the previous node is the last node
                           tail =preTargetedNode;
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
          	Hold*targetedNode =head->nexLF;
          	Hold*preTargetedNode =head;
          	//Algorithm to pre target a node
             for (int h =1; h <pos; h++)
       		{
        			preTargetedNode =targetedNode;
        			targetedNode =targetedNode->nexLF;
       		}
      		preTargetedNode->nexLF =targetedNode->nexLF;
      	    if (tail == targetedNode)
      	        tail =preTargetedNode;
      	    cout<<"\n\n\nDeleted Data : ("<<targetedNode->dF<<")"<<"\t\t\t\t-from ["<<pos<<"]";
      	    delete targetedNode;
      	    legnth--;
        	}
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
//Search for Data
void findData (int pos)
{
          while (pos < 0 || pos >=legnth)
               {    	 
                     cout<<"\n\n\nERROR"<<" Re-enter Position to Find DATA: ";
                     cin>>pos;
           	 }           
          Hold*targetedNode=head->nexLF;
          Hold*preTargetedNode =head;
          if (pos <1)
              targetedNode =head;
          else
          {
      		for (int h =1;h <pos ;h++)
        		{
         		    preTargetedNode =targetedNode;
         			targetedNode =targetedNode->nexLF;
        		}
          }
      		if (targetedNode != NULL)  
              	cout<<"\n\n\nPosition : ["<<pos<<"]"<<"\t\t\t\t\t-DATA Found   : ("<< targetedNode->dF<< ")";
      	else
              	cout<<"\n\n\nPosition : ["<<pos<<"]"<<"\t\t\t\t\t-DATA not found";          
}
//Search for Position
void findPosition (int val)
{ 
         Hold*targetedNode=head;
         int pos =0;
         int count =0;
         cout<<"\n\n\nDATA : ("<<val<<")"<<"\t\t\t\t\t-Found in ";
      		while (targetedNode != NULL)
      		{      	        	
       	      	    if (targetedNode->dF == val)
       	      	    {
      	      	     	cout<<"["<<pos<<"]";
      	      	     	count++;
       	      	    }
             		    targetedNode =targetedNode->nexLF;  
             	 	   pos++;
      		}
      		if (count == 0)
      		    cout<<"NOwhere";
}
void reverseNode()
{
    Hold*preTargetedNode =NULL;
    Hold*targetedNode =head;
    Hold*nexTargetedNode =targetedNode->nexLF;
    while (nexTargetedNode != NULL || targetedNode != NULL)
    {
        //1-save the addresses of the rest nodes
               nexTargetedNode =targetedNode->nexLF;
               //2-reverse the targeted node link direction
               targetedNode->nexLF =preTargetedNode;
               //3-move the all 3 pointers
               preTargetedNode =targetedNode;
               targetedNode =nexTargetedNode;
    }
    //make the last node is the head
    head =preTargetedNode;
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
#include <iostream>
using namespace std;
class linkedList {
	struct Knot
	{
		int dF;
		Knot*lF;
	};
	Knot*head;
	Knot*tail;
	int legnth;
public:
     linkedList()
     {
     	head =tail =NULL;
     	legnth =0;
     }
bool emptyNode()
{
     	return legnth == 0;
}
     //pushHead
void insertHeadD(int element)
{
     	Knot*hotNode=new Knot;
     	hotNode->dF =element;
     	if (legnth == 0)
     	{
     		head=tail=hotNode;
     		hotNode->lF =NULL;
     	}else 
     	        {
     	        	hotNode->lF =head;
     	        	head =hotNode;
     	        }
     	 legnth++;
}
     //popHead
void deleteFromHeadD()
{
         if (emptyNode())
            cout<<"There is nothing to delete";
         else if (legnth == 1)
         {
            delete head;
            tail =head =NULL;
            legnth--;
         }else 
                  {
                      Knot*targetedNode=head;
                      head =head->lF;
                      delete targetedNode;
                      legnth--;
                  }
}
     //pushTail
void insertTailD(int element)
{
     	Knot*hotNode =new Knot;
     	hotNode->dF =element;
     	if (legnth == 0)
     	{
     		head =tail =hotNode;
     		hotNode->lF =NULL;
     	}else 
     	        {
     	        	tail->lF =hotNode;
     	        	hotNode->lF =NULL;
     	        	tail=hotNode;
     	        }
     	     legnth++;
}
     //popTail
void deleteFromTailD()
{
         if (emptyNode())
           cout<<"There is nothing to delete";
         else if (legnth == 1)
         {
            delete tail;
            head =tail =NULL;
            legnth--;
         }else 
                  {
                       Knot*targetedNode =head->lF;
                       Knot*preTargetedNode =head;
                       while (targetedNode != tail)
                       {
                           preTargetedNode =targetedNode;
                           targetedNode =targetedNode->lF;
                       }
                           delete targetedNode;
                           preTargetedNode->lF =NULL;
                           tail =preTargetedNode;
                           legnth--;                     
                  }
}         
     //pushAtPos
void insertAtPos (int pos,int element)     
{
      	Knot*hotNode =new Knot;
      	hotNode->dF =element;
      	if (pos == 0)
      	insertHeadD(element);
      	else if (pos == legnth)
      	insertTailD(element);
      	else
      	{
      		Knot*preTargetedNode =head;
      		for (int h =1; h <pos ;h++)
      		{
      			preTargetedNode =preTargetedNode->lF;
      		}
      		hotNode->lF =preTargetedNode->lF;
      		preTargetedNode->lF =hotNode;
      		legnth++;
      	}
}
      //popFromPos
void deleteFromPos (int pos)     
{
      	Knot*preTargetedNode =head;
      	Knot*targetedNode;
      	if (emptyNode())
      	cout<<"There is nothing to delete";
      	else if (head->dF == pos)
      	deleteFromHeadD();
      	else if (pos == legnth)
      	deleteFromTailD();
      	else
      	{
      	    targetedNode =head->lF;
      	    preTargetedNode =head;
   while (targetedNode != NULL && targetedNode->dF != pos)
      		{
      			preTargetedNode =targetedNode;
      			targetedNode =targetedNode->lF;
      		}
      		if (targetedNode == NULL)
      		cout<<"Erorr 404 not found";
      		else
      		{      		    
      		preTargetedNode->lF =targetedNode->lF;
      		if (tail == targetedNode)
      		tail =preTargetedNode;
      		delete targetedNode;    
      		legnth--;
      		}     		
      	}
}     
void print()
{
      	Knot*currNode =head;
      	cout<<"Node -->";
      	while (currNode != NULL)
      	{
      		cout<<" ("<< currNode->dF <<") ";
      		currNode =currNode->lF;
      	}
      	cout<<endl;
}
void find (int pos)
{
          Knot*targetedNode=head;
      		for (int h =1; h <pos ;h++)
      		{
      			targetedNode =targetedNode->lF;
      		}
   
      	cout<<endl<<endl<<"\t\t\t\t\t\t-Founded Data : ("<< targetedNode->dF<< ")"<<endl<<endl<<endl;
          
}

      		     
      	
};
main()
{
	linkedList A;
	A.insertHeadD(10);
	A.insertTailD(40);
	A.insertAtPos(1,20);
	A.insertAtPos(2,30);
	A.print();
	A.deleteFromTailD();
	A.print();
	A.deleteFromHeadD();
	A.print();
	A.find(2);
	A.deleteFromPos(2);
	A.print();
	A.deleteFromPos(1);
	A.print();
	A.deleteFromHeadD();
	
	
	
	
}
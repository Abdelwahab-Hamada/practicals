#include <iostream>
using namespace std;

class linearProbing
{
    int size;
    int *arr;
    
    public:
    linearProbing(int );
    int lP(bool ,int ,int);
    void insert(int );
    int search(int );
    void remove (int );
    void show();    
    int hashing(int value){
        return (value%size);
    }
    
};
linearProbing::linearProbing (int size)//fixed
{
    this->size =size;
    arr =new int[size];//to create array with given size. 
}
//START linear probing method can change to any method (changeable)
int linearProbing::lP(bool insert,int index,int value)
{
    index =hashing(value);
    if (insert)
        value =NULL;    
    while (arr[index] != value)
    {
        index++;
        if (index >= size)
             index =0;
    }
    
    return index;
}
//END
void linearProbing::insert(int value)//fixed
{    
    int index =lP(1,index,value);
    arr[index] =value;
}

int linearProbing::search(int value)//fixed
{
    int index =lP(0,index,value);
    cout<<"Value."<<value<<" found in["<<index<<"]\n";        
    return index;
}

void linearProbing::remove(int value)//fixed
{
    int index =search(value);
    arr[index] =NULL;
    cout<<"     ."<<value<<" Deleted\n";
}

void linearProbing::show()//fixed
{
    cout<<endl;
    for (int index =0;index <size;index++)
    {
        cout<<"["<<index<<"]";
        int value =arr[index];    
        if (value == 0)
            cout<<".empty";
        else    
        cout<<"."<<value;
        cout<<endl;
    }
    cout<<endl;
}



int main()
{
     int a[] = {15, 11, 27, 8, 12,100}; 
     int n = sizeof(a)/sizeof(a[0]); 
    linearProbing hash(n);
    for (int i = 0; i < n; i++)  
    hash.insert(a[i]); 
    hash.show();
    hash.search(100);
    hash.remove(15);
    hash.show();
    return 0;
}
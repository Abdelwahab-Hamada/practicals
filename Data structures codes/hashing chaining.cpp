// CPP program to implement hashing with chaining 
#include<iostream> 
#include <list> 
using namespace std; 
  
class Hash 
{ 
    int BUCKETs;    // No. of BUCKETs 
  
    // Pointer to an array containing BUCKETs
    list<int> *tableBUCKET; 
public: 
    Hash(int V);  // Constructor 
  
    // inserts a key into hash tableBUCKET 
    void insertItem(int x); 
  
    // deletes a key from hash tableBUCKET 
    void deleteItem(int key); 
  
    // hash function to map values to key 
    int hashFunction(int x) { 
        return (x % BUCKETs); 
    } 
  
    void displayHash(); 
}; 
  
Hash::Hash(int b) 
{ 
    this->BUCKETs = b; 
    tableBUCKET = new list<int>[BUCKETs]; 
} 
  
void Hash::insertItem(int key) 
{ 
    int index = hashFunction(key); 
    tableBUCKET[index].push_back(key);  
} 
  
void Hash::deleteItem(int key) 
{ 
  // get the hash index of key 
  int index = hashFunction(key); 
  
  // find the key in (inex)th list 
  list <int> :: iterator i; 
  for (i = tableBUCKET[index].begin(); 
           i != tableBUCKET[index].end(); i++) { 
    if (*i == key) 
      break; 
  } 
  
  // if key is found in hash tableBUCKET, remove it 
  if (i != tableBUCKET[index].end()) 
    tableBUCKET[index].erase(i); 
} 
  
// function to display hash tableBUCKET 
void Hash::displayHash() { 
  for (int i = 0; i < BUCKETs; i++) { 
    cout << i; 
    for (auto x : tableBUCKET[i]) 
      cout << " --> " << x; 
    cout << endl; 
  } 
} 
  
// Driver program  
int main() 
{ 
  // array that contains keys to be mapped 
  int a[] = {15, 11, 27, 8, 12}; 
  int n = sizeof(a)/sizeof(a[0]); 
  
  // insert the keys into the hash tableBUCKET 
  Hash h(7);   // 7 is count of buckets in 
               // hash tableBUCKET 
  for (int i = 0; i < n; i++)  
    h.insertItem(a[i]);   
  
  // delete 12 from hash tableBUCKET 
  h.deleteItem(12); 
  
  // display the Hash tableBUCKET 
  h.displayHash(); 
  
  return 0; 
} 
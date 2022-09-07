/*Step 1: Get the timepoint before the function is called

#include <chrono> 
using namespace std::chrono; 
  
// Use auto keyword to avoid typing long 
// type definitions to get the timepoint 
// at this instant use function now() 
auto start = high_resolution_clock::now(); 
//Step 2: Get the timepoint after the function is called

#include <chrono> 
using namespace std::chrono; 
  
// After function call 
auto stop = high_resolution_clock::now(); 
//Step 3: Get the difference in timepoints and cast it to required units

// Subtract stop and start timepoints and 
// cast it to required unit. Predefined units 
// are nanoseconds, microseconds, milliseconds, 
// seconds, minutes, hours. Use duration_cast() 
// function. 
auto duration = duration_cast<microseconds>(stop - start); 
  
// To get the value of duration use the count() 
// member function on the duration object 
cout << duration.count() << endl; 

A complete C++ program demonstrating the procedure is given below. We fill up a vector with some random numbers and measure the time taken by sort() function to sort this vector.*/

// C++ program to find out execution time of 
// of functions 
#include <algorithm> 
#include <chrono> 
#include <iostream> 
using namespace std; 
using namespace std::chrono; 
  
// For demonstration purpose, we will fill up 
// a vector with random integers and then sort 
// them using sort function. We fill record 
// and print the time required by sort function 
int main() 
{ 
  
    vector<int> values(10000); 
  
    // Generate Random values 
    auto f = []() -> int { return rand() % 10000; }; 
  
    // Fill up the vector 
    generate(values.begin(), values.end(), f); 
  
    // Get starting timepoint 
    auto start = high_resolution_clock::now(); 
  
    // Call the function, here sort() 
    sort(values.begin(), values.end()); 
  
    // Get ending timepoint 
    auto stop = high_resolution_clock::now(); 
  
    // Get duration. Substart timepoints to  
    // get durarion. To cast it to proper unit 
    // use duration cast method 
    auto duration = duration_cast<microseconds>(stop - start); 
  
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl; 
  
    return 0; 
} 
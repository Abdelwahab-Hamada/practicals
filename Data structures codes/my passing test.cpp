#include <iostream>

template<typename T>
void print (T st)
{
    std::cout<<st;
}

int main()
{
    int x=0;
    print (x);
    print (" shit");
}
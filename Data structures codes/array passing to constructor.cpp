#include <iostream>

class ArrayClass{
public:
  ArrayClass(int* array, int size){
    a = new int[size];
    for (int i(0); i < size; i++) {
      this->a[i] = array[i];
    }
    this->size = size;
  }
  virtual ~ArrayClass(){
    delete[] a;
  }
  void print()
  {
      for (int i =0; i < size;i++)
      std::cout<<a[i];
  }
private:
  int* a;
  int size;
};

int main(int argc, char** argv){
  int array[3] = { 1, 2, 3 };
  ArrayClass a2(array, 3);
  a2.print();
  return 0;
}


/*int a[3]; // will allocate the space for 3 elements statically from the stack

int* a = new int[3]; // will allocate space for 3 elements dynamically from the heap

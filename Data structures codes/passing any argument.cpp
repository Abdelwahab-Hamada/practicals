#include <iostream>

class test_class{
public:
     template<typename T> static void member_function(T t){
        std::cout << "Argument: " << t << std::endl;
    }

};

int main(int argc, char ** argv){

    test_class::member_function(1);
    test_class::member_function("hello");
}
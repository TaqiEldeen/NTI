#include <iostream>

/***
    1- Members are private by default in classes
    2- Members are public by default in struct
    3- Access Modifiers are private, public, protected
*/
class TempClass
{
    int x;
};

struct TempStruct {
    int x;
};


class MyClass {
public:
    int x;

public:

    MyClass()
    {
        x = 0;
    }

    MyClass(int x)
        :x( x ) 
    {

    }

    void printWord(const char* str) {
        std::cout << str << std::endl;
    }
};

int main(void) {
    MyClass* myClass = new MyClass();

    myClass->printWord("TEST");
}
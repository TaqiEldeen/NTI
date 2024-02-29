#include <iostream>

class MyClass
{
private:
    int *data;

public:
    MyClass()
    {
        data = new int[100];
        for (int i = 0; i < 100; i++)
        {
            data[i] = i;
        }
    }

    MyClass(const MyClass &old)
    {
        data = new int[100];
        for (int i = 0; i < 100; i++)
        {
            data[i] = old.data[i];
        }
    }
};

int main()
{
    MyClass class1;
    MyClass class2(class1);
}
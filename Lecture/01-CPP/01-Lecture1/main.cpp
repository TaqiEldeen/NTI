#include <iostream>


inline __attribute__((always_inline)) void print(const char* text)
{
    std::cout << text << std::endl;
    print("Hello");
}

enum class Color 
{
    Red,
    Green,
    Blue
};

int main(int argc, const char** argv) {

    int value = 22;
    int &&x = 10;
    int &y = value;


    int *ptr = &value;


    for(auto x : {1, 2, 3, 4, 5})
    {
        std::cout << x << std::endl;
        x = 10;
    }

    print("Hello");

    return 0;
}
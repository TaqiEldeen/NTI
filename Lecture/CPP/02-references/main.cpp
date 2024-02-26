#include <iostream>

int main() {
    int num1 = 5;
    int num2 = 10;
    int result;

    int& ref1 = num1;
    int& ref2 = num2;
    int& ref3 = result;

    ref3 = ref1 + ref2;

    std::cout<<result<<std::endl;
}
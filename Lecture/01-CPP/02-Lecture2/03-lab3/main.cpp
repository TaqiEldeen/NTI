#include <iostream>

int main(int argc, const char** argv) {

    int *ptr = new int[10];

    ptr[0] = 10;    

    delete [] ptr;

    std::cout << "TEST"<< std::endl;

    return 0;
}
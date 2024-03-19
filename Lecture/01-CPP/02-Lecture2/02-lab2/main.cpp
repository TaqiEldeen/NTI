#include <iostream>

namespace newCalculator {
    int sum(int a, int b);
}

int newCalculator::sum(int a, int b) {
    return a + b + 100;
}

int sum(int a, int b) {
    return a + b + 99;
}

namespace calculator {
    int sum(int a, int b) {
        return (a + b) / 2;
    }
}



int main(void) {
    std::cout << "Sum newCalc: " << newCalculator::sum(5, 6) << std::endl;
    std::cout << "Sum normal: " << sum(5, 6) << std::endl;
    std::cout << "Sum calc: " << calculator::sum(5, 6) << std::endl;

    return 0;
}
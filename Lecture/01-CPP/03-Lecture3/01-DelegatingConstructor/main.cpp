#include <iostream>

class Car {
public:
    Car() : Car(0) {
        Car(0);
        std::cout << "Car()" << std::endl;
    }

    Car(int speed) : Car(speed, 0) {
        std::cout << "Car(int speed)" << std::endl;
    }

    Car(int speed, int gear) {
        std::cout << "Car(int speed, int gear)" << std::endl;
    }
};


int main() {
    Car car;
    // Car car2(10);
    // Car car3(20, 2);

    return 0;
}
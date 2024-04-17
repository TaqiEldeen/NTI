#include <iostream>


class Car {
private:
    int speed;
    int *ptr;
public:

    Car(){
        std::cout << "Car()" << std::endl;
    }

    Car(int speed) {
        this->speed = speed;
        ptr = new int(speed);
        std::cout << "Car(int speed)" << std::endl;
    }
    Car(int speed, int gear) {
        std::cout << "Car(int speed, int gear)" << std::endl;
    }

    /* Copy constuctor */
    Car(const Car &car) {
        this->speed = car.speed;
        /* Assign new heap memory for the current object with the value of the second object*/
        this->ptr = new int(*car.ptr);
        std::cout << "Copy constructor" << std::endl;
    }

    /* Copy assignment operator overloading */
    Car* operator= (const Car& car);

    ~Car() {
        delete ptr;
        std::cout << "Destructor" << std::endl;
    }
};

class Test
{
private:
    int x, y, z;

public:
    Test(/* args */);
    ~Test();
};

Test::Test(/* args */)
{
}

Test::~Test()
{
}


/* Copy assignment operator overloading */
Car* Car::operator= (const Car &car) {
    if (this == &car) {
        //return *this;
    }
    this->speed = car.speed;
    this->ptr = new int(*car.ptr);

    return new Car(5);
    //return *this;
}

int main(void) {
    // Car car(10);
    // Car car2;

    // Car *car3 = (car2 = car);

    // std::cout<<"Car speed: "<<*car2.ptr<<std::endl;

    Test test;

    std::cout << "Size is" << sizeof(test)<<std::endl;

    return 0;
}
#include    <iostream>

class Car
{
private:
    float fuel;
    int   speed;
    int   passenger;

public:
    Car(/* args */) {
        fuel = 0;
        speed = 0;
        passenger = 0;
    }

    ~Car();
    void setFuel(float f) {
        fuel = f;
    }
    void setSpeed(int);
    void setPassenger(int);
};


Car::~Car()
{
}


int main(int argc, char const *argv[])
{
    Car car;
    car.setFuel(10);
    return 0;
}

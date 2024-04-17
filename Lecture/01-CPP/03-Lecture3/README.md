# OOP

## Constructor Types
- Default Constructor
- Parameterized Constructor
- Copy Constructor
- Delegating Constructor


### To use the default constructor that is provided by the compiler:
``` C++
    /*Use the defualt constructor */
    TestClass() = default;

    /* Delete the copy constructor */
    TestClass(const TestClass& obj) = delete;

    /* Parameterized Constructor  */
    TestClass(int a) {

    }
```

You can prevent implicit casting in constructors using delete

``` c++
    /* This will prevent calling the constructor by float values */
    Car(float) = delete;
```

### Delegating Constructor

``` c++
    Car() : Car(0){
        std::cout << "Car()" << std::endl;
    }

    Car(int speed): Car(speed, 0){
        this->speed = speed;
        ptr = new int(speed);
        std::cout << "Car(int speed)" << std::endl;
    }
    Car(int speed, int gear) {
        std::cout << "Car(int speed, int gear)" << std::endl;
    }
```

> We use this instead of just calling the constructor inside the constructor to prevent making a new object


### nullptr

We use nullptr with move constructor as when freeing the object it wont crash

## Inherritance

#include <iostream>

class Calculator
{

public:
    int a, b;
    static int count;

public:
    Calculator(int a, int b)
        : a(a), b(b)
    {
        count++;
    }

    Calculator()
    {
        count++;
        a = 0;
        b = 0;
    }

    Calculator(const Calculator &calc)
    {
    }

    long int add(void)
    {
        return a + b;
    }

    long int minus(void)
    {
        return a - b;
    }

    long int multiply(void)
    {
        return a * b;
    }

    float divide(void)
    {
        return (float)a / b;
    }
};

int Calculator::count = 0;

std::ostream &operator<<(std::ostream &stream, const Calculator calc)
{
    std::cout << calc.a << "," << calc.b;
    return stream;
}

int main()
{
    Calculator calc(10, 20);

    std::cout << "ADD: " << calc.add() << std::endl;
    std::cout << "Div: " << calc.divide() << std::endl;
    std::cout << "Minus: " << calc.minus() << std::endl;
    std::cout << "Mul: " << calc.multiply() << std::endl;
    std::cout << calc << std::endl;
}
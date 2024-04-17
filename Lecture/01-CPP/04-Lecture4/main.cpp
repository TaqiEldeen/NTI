// #include <iostream>
// #include <memory>

// class Parent {
// public:
//     Parent() {
//         std::cout << "Parent constructor" << std::endl;
//     }
//     virtual ~Parent() {
//         std::cout << "Parent destructor" << std::endl;
//     }
// };

// class Child : public Parent {
// public:
//     int x;
//     Child() {
//         std::cout << "Child constructor" << std::endl;
//     }
//     ~Child() {
//         std::cout << "Child destructor" << std::endl;
//     }
// };

// int main() {
//     Child* child {new Child()}; 
//     Parent* parent = child; 
//     int x = 10;
//     std::shared_ptr<int> ptr = std::make_shared<int>(x);

//     //parent->x = 10;

//     delete child;
//     delete parent;
//     return 0;
// }


#include <iostream>
#include <memory>

class B; // Forward declaration

class A {
public:
    std::shared_ptr<B> b_ptr;
    ~A() { std::cout << "A destructor" << std::endl; }
};

class B {
public:
    std::shared_ptr<A> a_ptr; // Use weak_ptr to break the circular reference
    ~B() { std::cout << "B destructor" << std::endl; }
};

int main() {
    std::shared_ptr<A> a = std::make_shared<A>();
    std::shared_ptr<B> b = std::make_shared<B>();
    a->b_ptr = b;
    b->a_ptr = a;

    return 0;
}
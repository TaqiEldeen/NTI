#include <iostream>
#include <vector>
#include <map>

struct Employee {
    int id;
    std::string name;
    std::string department;
};

int main(int argc, const char** argv) {

    std::vector<Employee> vec { {12, "TaqiEldeen", "IT"}};

    vec.push_back( {31, "Ahmed", "HR"} );
    vec.push_back( {21, "Ahmed", "HR"} );

    std::map<int, Employee> map;

    map.insert( std::pair<int, Employee>(2, {21, "Ahmed", "HR"}) );


    for (auto iterator : vec) {
        std::cout<< vec.capacity() << std::endl;
    }
    
    return 0;
}
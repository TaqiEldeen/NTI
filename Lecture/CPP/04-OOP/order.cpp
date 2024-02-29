#include <iostream>
#include <ctime>

enum OrderStatus
{
    CREATE,
    SHIPPING,
    DELIVERED,
    PAID
};

class Order
{
public:
    char *createDate;

public:
    Order()
    {
        time_t now = time(0);
        createDate = ctime(&now);
    }
};

class Customer
{
private:
    std::string name;
    std::string deliveryAddress;
    std::string contact;
    bool active;
    int countOrder;
    Order orders[10];

public:
    Customer(std::string name, std::string deliveryAddress, std::string contact)
        : name(name), deliveryAddress(deliveryAddress), contact(contact)
    {
        countOrder = 0;
    }

    void add_order(Order newOrder)
    {
        orders[countOrder++] = newOrder;
    }

    void printCustomer()
    {
        std::cout << name << ", " << orders[0].createDate;
    }
};

int main()
{
    Customer customer("Taqi", "Giza", "0231003210");
    customer.add_order(Order());
    customer.printCustomer();
}
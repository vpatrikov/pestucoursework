#pragma once // include guard, kojto podsigurqva, che header file-a e vklyuchen samo edin pyt v cpp file

#include <iostream>
#include <string>
#include <vector>

typedef std::string string;

class menuItem
{
private:
    string item;
    double price;
    int itemId;

public:
    menuItem();
    menuItem(string item, double price, int itemId);

    string getItem() { return item; }
    void setItem(string item) { this->item = item; }

    double getPrice() { return price; }
    void setPrice(double price);

    int getitemId() { return itemId; }
    void setitemId(int itemId, std::vector<menuItem *> &menu);

    void printItem();

    ~menuItem() { /* std::cout << "\nDestructor for menuItem called\n"; */ }
};
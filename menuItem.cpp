#include "menuItem.h"

menuItem::menuItem()
{
    this->item = "";
    this->price = 0;
    this->itemId = 0;
}

menuItem::menuItem(string item, double price, int itemId)
{
    this->item = item;
    this->price = price;
    this->itemId = itemId;
}

void menuItem::setPrice(double price)
{
    if (price <= 0)
         throw std::invalid_argument("\nPrice cannot be equal or less then 0\n");
    else
        this->price = price;
}

void menuItem::setitemId(int itemId, std::vector<menuItem *> &menu)
{
    if (itemId <= 0)
        throw std::invalid_argument("\nInvalid ID - must be a positive integer.\n");

    for (int i = 0; i < menu.size(); i++)
    {
        if (menu[i]->getitemId() == itemId && menu[i] != this)
            throw std::invalid_argument("\nID is already used by another item.\n");
    }
    
    this->itemId = itemId;
}

void menuItem::printItem()
{
    printf("ID: %d, Name: %s, Price: %.2f\n", itemId, item.c_str(), price);
}
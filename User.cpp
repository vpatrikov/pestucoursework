#include "User.h"
#include "userGroup.h"

User::User()
{
    this->name = "";
    this->id = 0;
    group = nullptr;
}

User::User(string name, int id, userGroup *group)
{
    this->name = name;
    this->id = id;
    this->group = group;
}

void User::setUserId(int id, std::vector<User *> &users)
{
    if (id <= 0)
        throw std::invalid_argument("\nInvalid ID - must be a positive integer.\n");

    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]->getUserId() == id && users[i] != this)
            throw std::invalid_argument("\nID is already used by another user.\n");
    }

    this->id = id;
}

void User::printUser()
{
    printf("ID:%d, Name: %s, Group: %s, Price modifier: %.2f", id, name.c_str(),
    this->getUserGroup().c_str(), group->getPriceModifier());
}
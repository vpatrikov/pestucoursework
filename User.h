#pragma once

#include <iostream>
#include <vector>

#include "userGroup.h"

typedef std::string string;

class User
{
private:
    string name;
    int id;
    userGroup *group;

public:
    User();
    User(string name, int id, userGroup *group);

    string getName() { return name; }
    void setName(string name) { this->name = name; }

    int getUserId() { return id; }
    void setUserId(int id, std::vector<User *> &users);

    string getUserGroup() { return this->group->getgroupName(); }
    void setUserGroup(userGroup *group) { this->group = group; }

    void printUser();

    ~User() { /* std::cout << "\nDestructor for user called.\n"; */ }
};

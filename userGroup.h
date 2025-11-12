#pragma once

#include <iostream>

typedef std::string string;

class userGroup
{
private:
    string groupName;
    double priceModifier[2] = {0.9, 0.5};

public:
    userGroup();
    userGroup(string groupName);

    string getgroupName(){ return groupName;}

    double getPriceModifier();

    ~userGroup() { /*std::cout << "\nDestructor for userGroup called\n"; */ }
};
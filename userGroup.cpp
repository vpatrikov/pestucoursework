#include "userGroup.h"

userGroup::userGroup()
{
    this->groupName = "";
};

// v tozi sluchaj moje tozi konstruktor da se prieme i za setter za groupName
userGroup::userGroup(string groupName)
{
    std::transform(groupName.begin(), groupName.end(), groupName.begin(), ::tolower);
    this->groupName = groupName;
}

double userGroup::getPriceModifier()
    {
        if (groupName == "student")
        {
            return priceModifier[1];
        }
        else if (groupName == "teachers")
        {
            return priceModifier[0];
        }
        else
        {
            std::cout << "\nThere is no modifier - the user is not from this school.\n";
            return 1;
        }
    }
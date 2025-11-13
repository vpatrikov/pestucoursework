#include "file_manager.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include "menuItem.h"
#include "User.h"
#include "userGroup.h"

void saveData(const std::vector<menuItem *> &menu, const std::vector<User *> &users)
{

    std::ofstream menuFile("menuDB.txt");
    if (menuFile.is_open())
    {
        for (menuItem *item : menu)
        {
            menuFile << item->getitemId() << ","
                     << item->getItem() << ","
                     << item->getPrice() << "\n";
        }
        menuFile.close();
        std::cout << "\nMenu data saved to menuDB.txt\n\n";
    }
    else
    {
        std::cerr << "\nERROR: Unable to open menuDB.txt for writing.\n";
    }

    std::ofstream userFile("usersDB.txt");
    if (userFile.is_open())
    {
        for (User *user : users)
        {
            userFile << user->getUserId() << ","
                     << user->getName() << ","
                     << user->getUserGroup() << "\n";
        }
        userFile.close();
        std::cout << "\nUser data saved to usersDB.txt.\n\n";
    }
    else
    {
        std::cerr << "\nERROR: Unable to open usersDB.txt for writing.\n";
    }
}
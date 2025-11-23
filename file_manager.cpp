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

void loadData(std::vector<menuItem *> &menu, std::vector<User *> &users,
              userGroup *students_group, userGroup *teachers_group,
              userGroup *outside__people_group)
{
    std::ifstream menuFile("menuDB.txt");
    if (menuFile.is_open())
    {
        string line;

        while (std::getline(menuFile, line))
        {
            if (line.empty())
                continue;

            std::stringstream ss(line);
            string id_str, name, price_str;

            if (std::getline(ss, id_str, ',') &&
                std::getline(ss, name, ',') &&
                std::getline(ss, price_str, ','))
            {
                int id = std::stoi(id_str);
                double price = std::stod(price_str);

                menuItem *temp = new menuItem(name, price, id);

                menu.push_back(temp);
            }
        }
        menuFile.close();

        std::cout << "Menu has been loaded from menuDB.txt\n";
    }
    else
    {
        std::cerr << "Unable to open/read from menuDB.txt.\n";
    }

    std::ifstream userFile("usersDB.txt");
    if (userFile.is_open())
    {
        std::string line;
        while (std::getline(userFile, line))
        {
            if (line.empty())
                continue;

            std::stringstream ss(line);
            std::string idStr, name, groupName;

            if (std::getline(ss, idStr, ',') &&
                std::getline(ss, name, ',') &&
                std::getline(ss, groupName, ','))
            {
                int id = std::stoi(idStr);

                userGroup *assignedGroup = nullptr;

                if (groupName == "students")
                {
                    assignedGroup = students_group;
                }
                else if (groupName == "teachers")
                {
                    assignedGroup = teachers_group;
                }
                else
                {
                    assignedGroup = outside__people_group;
                }

                users.push_back(new User(name, id, assignedGroup));
            }
        }
        userFile.close();
        std::cout << "User data loaded successfully from usersDB.txt.\n";
    }
    else
    {
        std::cerr << "Unable to open/read from usersDB.txt.\n";
    }
}

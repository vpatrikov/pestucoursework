#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <vector>

typedef std::string string;

#include "menuItem.h"
#include "userGroup.h"
#include "User.h"
#include "file_manager.h"

userGroup *students_group = nullptr;
userGroup *teachers_group = nullptr;
userGroup *outside_people_group = nullptr;

int mainMenu()
{
    std::cout << "\n\n----------------------TU-Sofia Cafeteria Managment System (TUCMS)----------------------\n";
    std::cout << "\n1. Add an item to the menu\n";
    std::cout << "2. See all items on the menu\n";
    std::cout << "3. Add a user to the system\n";
    std::cout << "4. See all the users registered in the system\n";
    std::cout << "5. See the discount of the menu items for a certain user\n";
    std::cout << "6. Exit the program\n\n";
    std::cout << "---------------------------------------------------------------------------------------\n";

    int choice;

    do
    {
        std::cout << "\nChoice: ";
        try
        {
            std::cin >> choice;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                throw std::invalid_argument("Input should be an integer!");
                continue;
            }

            if (choice <= 0 || choice > 6)
            {
                throw std::out_of_range("Choice should be between 1 and 6.\n");
                continue;
            }

            return choice;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }

    } while (true);
}

menuItem *createAnItem(std::vector<menuItem *> &menu)
{
    menuItem *temp = new menuItem();
    string name;
    double price;
    int id;

    std::cout << "Enter the name of your item: ";
    std::cin >> name;
    temp->setItem(name);

    while (true)
    {
        std::cout << "Enter the price of your item: ";
        try
        {
            std::cin >> price;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                throw std::invalid_argument("\nInvalid input — please enter a number.\n");
            }

            if (price <= 0)
                throw std::invalid_argument("\nPrice must be greater than 0.\n");

            temp->setPrice(price);
            break;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << "\n";
        }
    }

    while (true)
    {
        std::cout << "Enter a unique ID for the item: ";
        try
        {
            std::cin >> id;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                throw std::invalid_argument("\nID should be a valid integer.\n");
                continue;
            }

            temp->setitemId(id, menu);
            break;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << "\n";
        }
    }
    std::cout << "\n\n";
    return temp;
}

User *createAUser(std::vector<User *> &users)
{
    User *temp = new User();
    std::string name;
    int id;
    std::string group;

    std::cout << "Enter the name of the user: ";
    std::cin >> name;
    temp->setName(name);

    while (true)
    {
        std::cout << "Enter a unique ID for the user: ";
        try
        {
            std::cin >> id;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                throw std::invalid_argument("\nInvalid ID - please enter a positive integer\n");
                continue;
            }

            temp->setUserId(id, users);
            break;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    std::cout << "Enter the user's group (teacher/student/none): ";
    std::cin >> group;

    std::transform(group.begin(), group.end(), group.begin(), ::tolower);

    if (group == "student")
        temp->setUserGroup(students_group);
    else if (group == "teacher")
        temp->setUserGroup(teachers_group);
    else
        temp->setUserGroup(outside_people_group);

    std::cout << "\n\n";
    return temp;
}
void consoleReadKey()
{
    std::cin.ignore(10000, '\n');
    std::cin.get();
}

int main()
{
    std::vector<menuItem *> menu;
    std::vector<User *> users;

    students_group = new userGroup("Students");
    teachers_group = new userGroup("Teachers");
    outside_people_group = new userGroup("None");

    loadData(menu, users, students_group, teachers_group, outside_people_group);

    if (menu.empty() && users.empty())
    {
        std::cout << "No data found. Starting with an empty system.\n";
    }

    int menuChoice;

    do
    {
        menuChoice = mainMenu();
        switch (menuChoice)
        {
        case 1:
        {
            menuItem *newItem = createAnItem(menu);
            menu.push_back(newItem);
            std::cout << "\nItem Added Successfully:\n";
            newItem->printItem();
            consoleReadKey();
            break;
        }

        case 2:
            if (menu.empty())
            {
                std::cout << "\nThe menu is empty.\n";
            }
            else
            {
                std::cout << "\nHere's what is on the menu at the moment:\n\n";
                for (size_t i = 0; i < menu.size(); i++)
                {
                    std::cout << '\n';
                    menu[i]->printItem();
                    std::cout << '\n';
                }
            }
            consoleReadKey();
            break;

        case 3:
        {
            User *newUser = createAUser(users);
            users.push_back(newUser);
            std::cout << "\nUser Added Successfully:\n";
            newUser->printUser();
            consoleReadKey();
            break;
        }

        case 4:
            if (users.empty())
            {
                std::cout << "\nNo users registered.\n";
            }
            else
            {
                std::cout << "\nRegistered Users:\n\n";
                for (size_t i = 0; i < users.size(); i++)
                {
                    users[i]->printUser();
                    std::cout << "----------------\n";
                }
            }
            consoleReadKey();
            break;

        case 5:
            std::cout << "\nFeature coming soon.\n";
            consoleReadKey();
            break;

        case 6:
            std::cout << "\nSaving data and exiting...\n";

            saveData(menu, users);

            for (size_t i = 0; i < menu.size(); i++)
            {
                delete menu[i];
            }

            for (size_t i = 0; i < users.size(); i++)
            {
                delete users[i];
            }

            delete teachers_group;
            delete students_group;
            delete outside_people_group;

            return 0;

        default:
            std::cout << "\nInvalid choice from the menu\n";
            consoleReadKey();
            break;
        }
    } while (true);
    return 0;
}
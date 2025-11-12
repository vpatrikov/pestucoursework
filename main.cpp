#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <vector>

typedef std::string string;

#include "menuItem.h"
#include "userGroup.h"
#include "User.h"

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

menuItem createAnItem(std::vector<menuItem *> &menu)
{
    menuItem temp;
    std::string name;
    double price;
    int id;

    std::cout << "Enter the name of your item: ";
    std::cin >> name;
    temp.setItem(name);

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

            temp.setPrice(price);
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

            temp.setitemId(id, menu);
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

User createAUser(std::vector<User *> &users)
{
    User temp;
    std::string name;
    int id;
    std::string group;

    std::cout << "Enter the name of the user: ";
    std::cin >> name;
    temp.setName(name);

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

            temp.setUserId(id, users);
            break;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    std::cout << "Enter the user's group (teacher/student/none): ";
    std::cin >> group;
    temp.setUserGroup(new userGroup(group));

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

    menuItem pizza("Pizza", 2.5, 1);
    menuItem spaghetti("Karbonara", 6, 2);
    menuItem musaka;

    menu.push_back(&pizza);
    menu.push_back(&spaghetti);
    menu.push_back(&musaka);

    musaka.setitemId(3, menu);
    musaka.setItem("Musaka");
    musaka.setPrice(3.99);

    userGroup students("students");
    userGroup teachers("teachers");
    userGroup outside_people("none");

    User student_1("Vladimir Patrikov", 1, &students);
    User student_2("Boncho Gabchev", 3, &students);
    User student_3;

    users.push_back(&student_1);
    users.push_back(&student_2);
    users.push_back(&student_3);

    student_3.setName("Martin");
    student_3.setUserId(2, users);
    student_3.setUserGroup(&students);

    menuItem newItem;
    User newUser;

    int menuChoice;

    do
    {
        menuChoice = mainMenu();
        switch (menuChoice)
        {
        case 1:
            newItem = createAnItem(menu);
            menu.push_back(&newItem);
            newItem.printItem();
            consoleReadKey();
            break;

        case 2:
            std::cout << "\nHere's what is on the menu at the moment:\n\n";
            for (int i = 0; i < menu.size(); i++)
            {
                std::cout << '\n';
                menu[i]->printItem();
                std::cout << '\n';
            }
            consoleReadKey();
            break;
        case 3:
            newUser = createAUser(users);
            users.push_back(&newUser);
            newUser.printUser();
            consoleReadKey();
            break;
        case 6:
            std::cout << "\nOk. Bye.\n";
            return 0;
        default:
            std::cout << "\nInvalid choice from the menu\n";
            consoleReadKey();
            break;
        }
    } while (true);
    return 0;
}
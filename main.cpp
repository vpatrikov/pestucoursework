#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <vector>

typedef std::string string;

class userGroup;
class User;

class menuItem
{
private:
    string item;
    double price;
    int itemId;

public:
    menuItem()
    {
        this->item = "";
        this->price = 0;
        this->itemId = 0;
    }

    menuItem(string item, double price, int itemId)
    {
        this->item = item;
        this->price = price;
        this->itemId = itemId;
    }

    string getItem() { return item; }
    void setItem(string item) { this->item = item; }

    double getPrice() { return price; }
    void setPrice(double price)
    {
        if (price <= 0)
            std::cout << "\nPrice cannot be equal or less then 0\n";
        else
            this->price = price;
    }

    int getitemId() { return itemId; }
    void setitemId(int itemId, std::vector<menuItem *> &menu)
    {
        if (itemId > 0)
        {
            bool idExists = false;
            for (int i = 0; i < menu.size(); i++)
            {
                if (menu[i]->getitemId() == itemId && menu[i] != this)
                {
                    std::cout << "\nID is already used by another item.\n";
                    idExists = true;
                    break;
                }
            }

            if (!idExists)
            {
                this->itemId = itemId;
            }
        }
        else
            std::cout << "\nInvalid ID - number should positive and larger than 0\n";
    }

    void printItem()
    {
        printf("ID: %d, Name: %s, Price: %.2f\n", itemId, item.c_str(), price);
    }

    ~menuItem() { /* std::cout << "\nDestructor for menuItem called\n"; */ }
};

class userGroup
{
private:
    string groupName;
    double priceModifier[2] = {0.9, 0.5};

public:
    userGroup()
    {
        this->groupName = "";
    };

    // v tozi sluchaj moje tozi konstruktor da se prieme i za setter za groupName
    userGroup(string groupName)
    {
        std::transform(groupName.begin(), groupName.end(), groupName.begin(), ::tolower);
        this->groupName = groupName;
    }

    string getgroupName()
    {
        return groupName;
    }

    double getPriceModifier()
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

    ~userGroup() { /*std::cout << "\nDestructor for userGroup called\n"; */ }
};

class User
{
private:
    string name;
    int id;
    userGroup *group;

public:
    User()
    {
        this->name = "";
        this->id = 0;
        group = nullptr;
    }

    User(string name, int id, userGroup* group)
    {
        this->name = name;
        this->id = id;
        this->group = group;
    }
    string getName() { return name; }
    void setName(string name) { this->name = name; }

    void setUserId(int id, std::vector<User *> &users)
    {
        if (id > 0)
        {
            bool idExists = false;
            for (int i = 0; i < users.size(); i++)
            {
                if (users[i]->getUserId() == id && users[i] != this)
                {
                    std::cout << "\nID is already used by another item.\n";
                    idExists = true;
                    break;
                }
            }

            if (!idExists)
            {
                this->id = id;
            }
        }
        else
            std::cout << "\nInvalid ID - number should positive and larger than 0\n";
    }

    int getUserId() { return id; }

    void setUserGroup(userGroup *group)
    {
        this->group = group;
    }

    ~User() { /* std::cout << "\nDestructor for user called.\n"; */ }
};

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
                throw std::invalid_argument("Invalid input — please enter a number.");
            }

            if (price <= 0)
                throw std::invalid_argument("Price must be greater than 0.");

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
                throw std::invalid_argument("ID should be a valid integer.");
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

int main()
{
    std::vector<menuItem *> menu;
    std::vector <User *> users; 
    int menuChoice = mainMenu();

    menuItem pizza("Pizza", 2.5, 1);
    menuItem spaghetti("Karbonara", 6, 2);
    menuItem musaka;

    menu.push_back(&pizza);
    menu.push_back(&spaghetti);
    menu.push_back(&musaka);

    musaka.setitemId(3, menu);
    musaka.setItem("Musaka");
    musaka.setPrice(3.99);

    userGroup students ("students");
    userGroup teachers ("teachers");
    userGroup teachers ("none");

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

    switch (menuChoice)
    {
    case 1:
        newItem = createAnItem(menu);
        menu.push_back(&newItem);
        newItem.printItem();
        break;

    case 2:
        std::cout << "\nHere's what is on the menu at the moment:\n\n";
        for (int i = 0; i < menu.size(); i++)
        {
            std::cout << '\n';
            menu[i]->printItem();
            std::cout << '\n';
        }
        break;
    default:
        std::cout << "\nInvalid choice from the menu\n";
        break;
    }

    return 0;
}
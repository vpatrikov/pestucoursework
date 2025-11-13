#pragma once

#include <vector>
#include <string>

class menuItem;
class userGroup;
class User;

void saveData(const std::vector<menuItem *> &menu, const std::vector<User *> &users);
void loadData(std::vector<menuItem *> &menu, std::vector<User *> &users,
              userGroup *students_group, userGroup *teachers_group,
              userGroup *outside__people_group);
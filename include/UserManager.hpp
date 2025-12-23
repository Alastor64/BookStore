#pragma once
#include "User.hpp"
#include "Stack.hpp"
#include <vector>
#include "Map.hpp"
namespace UserManager
{
    Stack<std::pair<int, PRIVILEGE>> &logedUsers();
    Map<decltype(User::ID)> &mapID();
    int userAdd(const std::vector<std::string> &S);
}
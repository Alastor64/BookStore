#pragma once
#include "User.hpp"
#include "Stack.hpp"
#include <vector>
#include "Map.hpp"
namespace UserManager
{
    Stack<std::pair<int, PRIVILEGE>> logedUsers("logedUsers");
    IO<User, 0> *Data()
    {
        return IO<User, 0>::instance("Users");
    }
    Map<decltype(User::ID)> mapID("UsersSortedByID");
    int userAdd(const std::vector<std::string> &S);
}
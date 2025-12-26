#pragma once
#include "User.hpp"
#include "Stack.hpp"
#include <vector>
#include "Map.hpp"
namespace UserManager
{
    IO<User, 0> &users();
    Stack<std::pair<int, PRIVILEGE>> &logedUsers();
    Map<decltype(User::ID)> &mapID();
    Stack<int> &selectedBooks();
    int userAdd(const std::vector<std::string> &S);
    int passwd(const std::vector<std::string> &S);
    int Register(std::vector<std::string> &S);
    int su(const std::vector<std::string> &S, PRIVILEGE P);
    int logOut(const std::vector<std::string> &S);
    int Delete(const std::vector<std::string> &S);
    int getPrivilege(PRIVILEGE &P);
    int getIndex(int &Pndex);
    int exit(const std::vector<std::string> &S);
    int logedClear();
}
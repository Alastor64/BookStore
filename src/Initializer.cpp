#include "Initializer.hpp"
#include "UserManager.hpp"
#include "User.hpp"
#include "Commander.hpp"
#include "BookManager.hpp"
#include "BigBrother.hpp"
#include <filesystem>
#include <iostream>
#include <iomanip>
namespace FS = std::filesystem;
void Init()
{
    std::cout << std::fixed << std::setprecision(2);
    if (!FS::exists("data"))
        FS::create_directory("data");
    UserManager::logedClear();
    int index = UserManager::mapID().show(std::string("root"));
    // std::cout << index << "\n";
    std::vector<std::string> tmp;
    if (index == END_INT)
    {
        tmp.clear();
        tmp.push_back("root");
        tmp.push_back("sjtu");
        tmp.push_back(std::to_string(static_cast<int>(PRIVILEGE::BOSS)));
        tmp.push_back("Alastor");
        int _ = UserManager::userAdd(tmp, PRIVILEGE::BIG_BROTHER);
        // std::cout << _ << "\n";
    }
    // tmp.clear();
    // tmp.push_back("root");
    // tmp.push_back("sjtu");
    // UserManager::su(tmp, PRIVILEGE::BIG_BROTHER);
    // printf("oo\n");
}

IO<User> &UserManager::users()
{
    static IO<User> tmp("Users", 1);
    return tmp;
}

Map<decltype(User::ID)> &UserManager::mapID()
{
    static Map<decltype(User::ID)> tmp("UsersSortedByID");
    return tmp;
}

Stack<std::pair<int, PRIVILEGE>> &UserManager::logedUsers()
{
    static Stack<std::pair<int, PRIVILEGE>> tmp("LogedUsers");
    return tmp;
}

Stack<int> &UserManager::selectedBooks()
{
    static Stack<int> tmp("SlectedBooks");
    return tmp;
}
IO<Book> &BookManager::books()
{
    static IO<Book> tmp("Books", 1);
    return tmp;
}

Map<decltype(Book::ISBN)> &BookManager::mapISBN()
{
    static Map<decltype(Book::ISBN)> tmp("BooksSortedByISBN");
    return tmp;
}
Map<decltype(Book::author)> &BookManager::mapAuthor()
{
    static Map<decltype(Book::author)> tmp("BooksSortedByAuthor");
    return tmp;
}
Map<decltype(Book::name)> &BookManager::mapName()
{
    static Map<decltype(Book::name)> tmp("BooksSortedByName");
    return tmp;
}
Map<decltype(Book::keywords)> &BookManager::mapKeywords()
{
    // printf("fuck!\n"); // #
    static Map<decltype(Book::keywords)> tmp("BooksSortedByKeywords");
    return tmp;
}

Stack<Finance> &BigBrother::cashLog()
{
    static Stack<Finance> tmp("cashLog");
    return tmp;
}
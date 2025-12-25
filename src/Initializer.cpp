#include "Initializer.hpp"
#include "UserManager.hpp"
#include "User.hpp"
#include "Commander.hpp"
#include <filesystem>
namespace FS = std::filesystem;
void Init()
{
    if (!FS::exists("data"))
        FS::create_directory("data");
    UserManager::logedUsers().clear();
    UserManager::selectedBooks().clear();
    int index = UserManager::mapID().show(std::string("root"));
    std::vector<std::string> tmp;
    if (index == END_INT)
    {
        tmp.clear();
        tmp.push_back("root");
        tmp.push_back("sjtu");
        tmp.push_back(std::to_string(static_cast<int>(PRIVILEGE::BOSS)));
        tmp.push_back("Alastor");
        UserManager::userAdd(tmp);
    }
    tmp.clear();
    tmp.push_back("root");
    tmp.push_back("sjtu");
    UserManager::su(tmp, PRIVILEGE::BOSS);
}

IO_base *User::Data()
{
    return IO<User>::instance("Users");
}

Map<decltype(User::ID)> &UserManager::mapID()
{
    static Map<decltype(User::ID)> tmp("UsersSortedByID");
    return tmp;
}

Stack<std::pair<int, PRIVILEGE>> &UserManager::logedUsers()
{
    static Stack<std::pair<int, PRIVILEGE>> tmp("logedUsers");
    return tmp;
}

Stack<int> &UserManager::selectedBooks()
{
    static Stack<int> tmp("slectedBooks");
    return tmp;
}
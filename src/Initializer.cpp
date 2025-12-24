#include "Initializer.hpp"
#include "UserManager.hpp"
#include "User.hpp"
#include <filesystem>
namespace FS = std::filesystem;
void Init()
{
    if (!FS::exists("data"))
        FS::create_directory("data");
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
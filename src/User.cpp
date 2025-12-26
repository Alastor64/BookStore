#include "User.hpp"
#include <iostream>
User::User()
{
    logedTimes = 0;
}
User::User(int _THIS)
{
    this->assign(_THIS);
}
bool isPRIVILEGE(const std::string &s)
{
    // std::cout << s << "\n";
    static const std::string GUEST(
        std::to_string(static_cast<int>(PRIVILEGE::GUEST)));
    static const std::string VISITOR(
        std::to_string(static_cast<int>(PRIVILEGE::VISITOR)));
    static const std::string STARFF(
        std::to_string(static_cast<int>(PRIVILEGE::STARFF)));
    static const std::string BOSS(
        std::to_string(static_cast<int>(PRIVILEGE::BOSS)));
    if (s == GUEST)
        return 0;
    if (s == VISITOR)
        return 0;
    if (s == STARFF)
        return 0;
    if (s == BOSS)
        return 0;
    return 1;
}
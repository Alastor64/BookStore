#include "User.hpp"
User::User()
{
    logedTimes = 0;
}
User::User(int _THIS) : Base(_THIS) {}
bool isPRIVILEGE(const std::string &s)
{
    if (s.length() != 1)
        return 0;
    switch (s.at(0))
    {
    case static_cast<int>(PRIVILEGE::GUEST):
    case static_cast<int>(PRIVILEGE::VISITOR):
    case static_cast<int>(PRIVILEGE::STARFF):
    case static_cast<int>(PRIVILEGE::BOSS):
        break;
    default:
        return 0;
    }
    return 1;
}
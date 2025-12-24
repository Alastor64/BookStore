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
    case '0':
    case '1':
    case '3':
    case '7':
        break;
    default:
        return 0;
    }
    return 1;
}
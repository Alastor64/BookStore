#include "User.hpp"
void User::clear()
{
    logedTimes = 0;
}
bool isUserPRIVILEGE(const std::string &s)
{
    static const std::string GUEST(
        std::to_string(static_cast<int>(PRIVILEGE::GUEST)));
    static const std::string STAFF(
        std::to_string(static_cast<int>(PRIVILEGE::STAFF)));
    static const std::string BOSS(
        std::to_string(static_cast<int>(PRIVILEGE::BOSS)));
    if (s == GUEST)
        return 0;
    if (s == STAFF)
        return 0;
    if (s == BOSS)
        return 0;
    return 1;
}
#pragma once
#include "Name.hpp"
enum class PRIVILEGE
{
    VISITOR = 0,
    GUEST = 1,
    STAFF = 3,
    BOSS = 7,
    BIG_BROTHER = 999,
};
bool isUserPRIVILEGE(const std::string &s);
class User
{
public:
    Name<30, NAME_TYPE::NUM_LETTER> ID;
    Name<30, NAME_TYPE::NUM_LETTER> password;
    Name<30, NAME_TYPE::VISIBLE> name;
    PRIVILEGE privilege;
    int logedTimes;
    void clear();
};

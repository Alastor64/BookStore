#pragma once
#include "Base.hpp"
#include "Name.hpp"
enum class PRIVILEGE
{
    VISITOR = 0,
    GUEST = 1,
    STARFF = 3,
    BOSS = 7,
};
bool isPRIVILEGE(const std::string &s);
class User : public Base
{
protected:
    IO_base *Data() override;

public:
    Name<30, NAME_TYPE::NUM_LETTER> ID;
    Name<30, NAME_TYPE::NUM_LETTER> password;
    Name<30, NAME_TYPE::VISIBLE> name;
    PRIVILEGE privilege;
    int logedTimes;
    User();
    User(int _THIS);
};

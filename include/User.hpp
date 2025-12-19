#pragma once
#include "Base.hpp"
#include "Name.hpp"
namespace USER
{
    enum PRIVILEGE
    {
        VISITOR = 0,
        GUEST = 1,
        STARFF = 3,
        BOSS = 7,
    };
}
class User : public Base
{
protected:
    IO_base *Data() override
    {
        return IO<User>::instance("Users");
    }

public:
    Name<30, NAME::NUM_LETTER> ID;
    Name<30, NAME::NUM_LETTER> password;
    Name<30, NAME::VISIBLE> name;
    USER::PRIVILEGE privilege;
    User() {}
    User(int _THIS);
};

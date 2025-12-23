#include "UserManager.hpp"
int UserManager::userAdd(const std::vector<std::string> &S)
{
    if (S.size() != 4)
        return -1;
    User u;
    if (u.ID.check(S.at(0)))
    {
        u.ID = S.at(0);
        std::vector<int> tmp;
        mapID().show(u.ID, tmp);
        if (!tmp.empty())
            return 1;
    }
    else
        return 2;
    if (u.password.check(S.at(1)))
        u.password = S.at(1);
    else
        return 3;
    if (isPRIVILEGE(S.at(2)))
        u.privilege = static_cast<PRIVILEGE>(S.at(2).at(0) - '0');
    else
        return 4;
    if (u.name.check(S.at(3)))
        u.name = S.at(3);
    else
        return 5;
    u.write();
    mapID().insert(std::make_pair(u.ID, u.THIS));
    return 0;
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
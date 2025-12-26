#include "UserManager.hpp"
namespace UserManager
{
    User u;
    std::vector<std::string> tmp;
}
int UserManager::userAdd(const std::vector<std::string> &S)
{
    if (S.size() != 4)
        return -1;
    if (u.ID.check(S.at(0)))
    {
        u.ID = S.at(0);
        int j = mapID().show(u.ID);
        if (j != END_INT)
            return 1;
    }
    else
        return 2;
    if (u.password.check(S.at(1)))
        u.password = S.at(1);
    else
        return 3;
    if (!isPRIVILEGE(S.at(2)))
        u.privilege = static_cast<PRIVILEGE>(S.at(2).at(0) - '0');
    else
        return 4;
    if (u.name.check(S.at(3)))
        u.name = S.at(3);
    else
        return 5;
    u.clear();
    mapID().insert(std::make_pair(u.ID, users().Write(&u)));
    return 0;
}
int UserManager::passwd(const std::vector<std::string> &S)
{
    if (S.size() < 2 || S.size() > 3)
        return -1;
    int index = END_INT;
    if (u.ID.check(S.at(0)))
    {
        u.ID = S.at(0);
        index = mapID().show(u.ID);
        if (index == END_INT)
            return 1;
        else
            users().Read(&u, index);
    }
    if (S.size() == 3)
    {
        if (!u.password.check(S.at(1)))
            return 2;
        decltype(u.password) C(S.at(1));
        if (u.password != C)
            return 3;
    }
    if (!u.password.check(S.back()))
        return 4;
    u.password = S.back();
    users().Update(&u, index);
    return 0;
}
int UserManager::Register(std::vector<std::string> &S)
{
    if (S.size() != 3)
        return -1;
    S.insert(S.begin() + 2, "1");
    return userAdd(S);
}
int UserManager::su(const std::vector<std::string> &S, PRIVILEGE P)
{
    if (S.size() != 2 && S.size() != 1)
        return -1;
    if (!u.ID.check(S.at(0)))
        return 1;
    int index = mapID().show(S.at(0));
    if (index == END_INT)
        return 2;
    users().Read(&u, index);
    if (u.privilege >= P || S.size() == 2)
    {
        if (S.size() != 2)
            return -2;
        if (!u.password.check(S.at(1)))
            return 3;
        decltype(u.password) C(S.at(1));
        if (u.password != C)
            return 4;
    }
    // std::cout << u.ID.at(0) << " " << u.password.at(0) << " " << u.name.at(0) << "\n";
    logedUsers().push(std::make_pair(index, u.privilege));
    selectedBooks().push(END_INT);
    u.logedTimes++;
    users().Update(&u, index);
    return 0;
}
int UserManager::logOut(const std::vector<std::string> &S)
{
    if (!S.empty())
        return -1;
    if (logedUsers().empty())
        return 1;
    // printf("u=\n");
    int index = logedUsers().top().first;
    users().Read(&u, index);
    // printf("aab\n");
    u.logedTimes--;
    users().Update(&u, index);
    logedUsers().pop();
    selectedBooks().pop();
    return 0;
}
int UserManager::Delete(const std::vector<std::string> &S)
{
    if (S.size() != 1)
        return -1;
    if (!u.ID.check(S.at(0)))
        return 1;
    int index = mapID().show(S.at(0));
    if (index == END_INT)
        return 2;
    users().Read(&u, index);
    if (u.logedTimes)
        return 3;
    users().Delete(index);
    mapID().eraze(std::make_pair(u.ID, index));
    return 0;
}
int UserManager::getPrivilege(PRIVILEGE &P)
{
    if (logedUsers().empty())
        return 1;
    P = logedUsers().top().second;
    return 0;
}
int UserManager::getIndex(int &Index)
{
    if (logedUsers().empty())
        return 1;
    Index = logedUsers().top().first;
    return 0;
}

int UserManager::logedClear()
{
    tmp.clear();
    while (!logOut(tmp))
        ;
    return 0;
}
int UserManager::exit(const std::vector<std::string> &S)
{
    if (!S.empty())
        return -1;
    logedClear();
    std::exit(0);
}
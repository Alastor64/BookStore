#include "Commander.hpp"
namespace Commander
{
    std::string tmp1;
    std::vector<std::string> tmp2;
}
int Commander::scanfString(it &L, it &R, std::string &S, const it &end)
{
    while (L != end && *L == SPLIT_CHAR)
        L++;
    if (L == end)
        return 1;
    R = ++L;
    while (R != end && *R != SPLIT_CHAR)
        R++;
    S.assign(L, R);
    return 0;
}
int Commander::excute(const std::string &inPut, std::string &outPut)
{
    if (!Name<MAX_COMMAND_LENGTH, NAME_TYPE::COMMAND>::check(inPut))
        return -1;
    it L = inPut.begin(), R;
    if (scanfString(L, R, tmp1, inPut.end())) // 仅有空格
        return 0;
    tmp2.clear();
    while (1)
    {
        L = R;
        tmp2.push_back("");
        if (scanfString(L, R, tmp2.back(), inPut.end()))
        {
            tmp2.pop_back();
            break;
        }
    }
    if (tmp1 == "su")
    {
        PRIVILEGE p;
        if (UserManager::getPrivilege(p))
            return -2;
        return UserManager::su(tmp2, p);
    }
    if (tmp1 == "logout")
        return UserManager::logOut(tmp2);
    if (tmp1 == "register")
        return UserManager::Register(tmp2);
    if (tmp1 == "passwd")
        return UserManager::passwd(tmp2);
    if (tmp1 == "useradd")
        return UserManager::userAdd(tmp2);
    if (tmp1 == "delete")
        return UserManager::Delete(tmp2);
    return -3;
}
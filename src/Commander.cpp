#include "Commander.hpp"
#include "UserManager.hpp"
#include "BookManager.hpp"
#include "BigBrother.hpp"
namespace Commander
{
    std::string tmp1;
    std::vector<std::string> tmp2;
    std::string tmpIn;
    Report r;
    User u;
}
int Commander::scanfString(it &L, std::string &S, const it &end)
{
    it R;
    while (L != end && *L == SPLIT_CHAR)
        L++;
    if (L == end)
        return 1;
    (R = L)++;
    while (R != end && *R != SPLIT_CHAR)
        R++;
    S.assign(L, R);
    L = R;
    return 0;
}
int Commander::interpreter(const std::string &S)
{
    it L = S.begin();
    if (scanfString(L, tmp1, S.end())) // 仅有空格
    {
        tmp1.clear();
        return 0;
    }
    tmp2.clear();
    while (1)
    {
        tmp2.push_back("");
        if (scanfString(L, tmp2.back(), S.end()))
        {
            tmp2.pop_back();
            break;
        }
    }
    return 0;
}
int Commander::excute(const std::string &inPut)
{
    if (interpreter(inPut))
        return -1;
    if (tmp1.empty())
        return 0;
    if (tmp1 == "su")
        return UserManager::su(tmp2, UserManager::getPrivilege());
    if (tmp1 == "logout")
    {
        if (UserManager::getPrivilege() >= PRIVILEGE::GUEST)
            return UserManager::logOut(tmp2);
        else
            return -4;
    }
    if (tmp1 == "register")
        return r.operation = COMMAND_TYPE::ADD, UserManager::Register(tmp2);
    if (tmp1 == "passwd")
    {
        if (UserManager::getPrivilege() >= PRIVILEGE::GUEST)
            return r.operation = COMMAND_TYPE::PASSWD, UserManager::passwd(tmp2, UserManager::getPrivilege());
        else
            return -5;
    }
    if (tmp1 == "useradd")
    {
        if (UserManager::getPrivilege() >= PRIVILEGE::STAFF)
            return r.operation = COMMAND_TYPE::ADD, UserManager::userAdd(tmp2, UserManager::getPrivilege());
        else
            return -6;
    }
    if (tmp1 == "delete")
    {
        if (UserManager::getPrivilege() >= PRIVILEGE::BOSS)
            return r.operation = COMMAND_TYPE::DELETE, UserManager::Delete(tmp2);
        else
            return -7;
    }
    if (tmp1 == "exit" || tmp1 == "quit")
        return UserManager::exit(tmp2);
    if (tmp1 == "show")
    {
        if (!tmp2.empty() && tmp2.front() == "finance")
            if (UserManager::getPrivilege() >= PRIVILEGE::BOSS)
                return BigBrother::show_finance(tmp2);
            else
                return -13;
        else if (UserManager::getPrivilege() >= PRIVILEGE::GUEST)
            return BookManager::show(tmp2);
        else
            return -8;
    }
    if (tmp1 == "buy")
        if (UserManager::getPrivilege() >= PRIVILEGE::GUEST)
        {
            Finance Gain;
            Gain.isCost = 0;
            r.operation = COMMAND_TYPE::BUY;
            int _ = BookManager::buy(tmp2, Gain.cash);
            if (_)
                return _;
            else
            {
                BigBrother::cashLog().push(Gain);
                return 0;
            }
        }
        else
            return -9;
    if (tmp1 == "select")
        if (UserManager::getPrivilege() >= PRIVILEGE::STAFF)
            return r.operation = COMMAND_TYPE::CREATE, BookManager::select(tmp2);
        else
            return -10;
    if (tmp1 == "modify")
        if (UserManager::getPrivilege() >= PRIVILEGE::STAFF)
            return r.operation = COMMAND_TYPE::MODIFY, BookManager::modify(tmp2);
        else
            return -11;
    if (tmp1 == "import")
        if (UserManager::getPrivilege() >= PRIVILEGE::STAFF)
        {
            Finance Cost;
            Cost.isCost = 1;
            r.operation = COMMAND_TYPE::IMPORT;
            int _ = BookManager::import(tmp2, Cost.cash);
            if (_)
                return _;
            else
            {
                BigBrother::cashLog().push(Cost);
                return 0;
            }
        }
        else
            return -12;
    if (tmp1 == "report")
    {
        if (UserManager::getPrivilege() < PRIVILEGE::BOSS)
            return -13;
        if (tmp2.at(0) == "finance")
            return BigBrother::report_finance(tmp2);
        if (tmp2.at(0) == "employee")
            return BigBrother::report_employee(tmp2);
    }
    if (tmp1 == "log")
    {
        if (UserManager::getPrivilege() < PRIVILEGE::BOSS)
            return -14;
        return BigBrother::log(tmp2);
    }
    return -3;
}

int Commander::receptionist()
{
    bool DEBUG = 0;
    std::fstream Log;
    if (DEBUG)
        Log.open("log.out", std::ios::out);
    int num = 0;
    while (std::getline(std::cin, tmpIn))
    {
        r.T = time(NULL);
        int index;
        if (UserManager::getIndex(index))
            r.account = std::string("");
        else
        {
            UserManager::users().Read(&u, index);
            r.account = u.ID;
        }
        r.privilege = UserManager::getPrivilege();
        num++;
        int E;
        if (E = excute(tmpIn))
        {
            std::cout << INVALID;
            if (DEBUG)
                printf("<%d,%d>", num, E);
            std::cout << std::endl;
        }
        else if (DEBUG)
            Log << tmpIn << std::endl;
    }
    excute("exit");
    return 0;
}
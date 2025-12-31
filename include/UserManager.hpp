#pragma once
#include "User.hpp"
#include "Stack.hpp"
#include <vector>
#include "Map.hpp"
#include "BigBrother.hpp"
#include "Commander.hpp"
namespace UserManager
{
    IO<User> &users();                                           // 记录所有User类，记index为每个User类在其中的索引
    Stack<std::pair<int, PRIVILEGE>> &logedUsers();              // 登录栈
    Map<decltype(User::ID)> &mapID();                            // 有序对（用户ID，index）
    Stack<int> &selectedBooks();                                 // 选择的书，默认为END
    int userAdd(const std::vector<std::string> &S, PRIVILEGE p); // 指令 创建帐户
    int passwd(const std::vector<std::string> &S, PRIVILEGE p);  // 指令 修改密码
    int Register(std::vector<std::string> &S);                   // 指令 注册帐户
    int su(const std::vector<std::string> &S, PRIVILEGE P);      // 指令 登录帐户
    int logOut(const std::vector<std::string> &S);               // 指令 注册帐户
    int Delete(const std::vector<std::string> &S);               // 指令 删除帐户
    PRIVILEGE getPrivilege();                                    // 获取当前权限
    int getIndex(int &Index);                                    // 获取当前账户index存入Index，若未登录返回非0值
    int getBook();                                               // 获取当前选择的书本index
    int exit(const std::vector<std::string> &S);                 // 指令 正常退出系统
    int logedClear();                                            // 注销所有账户
}
#pragma once
#include "Name.hpp"
enum class PRIVILEGE // 权限类型
{
    VISITOR = 0,
    GUEST = 1,
    STAFF = 3,
    BOSS = 7,
    BIG_BROTHER = 999,
};
bool isUserPRIVILEGE(const std::string &s); // 是否为账户权限
class User                                  // 账户信息
{
public:
    Name<30, NAME_TYPE::NUM_LETTER> ID;       // 用户ID
    Name<30, NAME_TYPE::NUM_LETTER> password; // 密码
    Name<30, NAME_TYPE::VISIBLE> name;        // 用户名
    PRIVILEGE privilege;                      // 权限
    int logedTimes;                           // 登录重数
    void clear();                             // 清楚登录重数
};

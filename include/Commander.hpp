#pragma once
#include "UserManager.hpp"
#include "BigBrother.hpp"
namespace Commander // 负责读入指令，权限判段，执行
{
    extern Report r;
    typedef std::string::const_iterator it;
    int excute(const std::string &inPut);                  // 执行指令
    int scanfString(it &L, std::string &S, const it &end); // 从string(L,end)中读取一个词存入S，更新L
    int receptionist();                                    // 模拟终端
    int interpreter(const std::string &S);                 // 指令分词 将第一个词存入tmp1 剩余的存入tmp2
}
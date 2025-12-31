#pragma once
#include "BigBrother.hpp"
#include <iostream>
#include <fstream>
constexpr int MAX_COMMAND_LENGTH = 500;             // 最长可接受指令长度
constexpr char SPLIT_CHAR = ' ';                    // 指令分词符
const std::string INVALID = std::string("Invalid"); // 非法反馈输出
namespace Commander                                 // 负责读入指令，权限判段，执行
{
    extern Report r;
    typedef std::string::const_iterator it;
    int excute(const std::string &inPut);                  // 执行指令
    int scanfString(it &L, std::string &S, const it &end); // 从string(L,end)中读取一个词存入S，更新L
    int receptionist();                                    // 模拟终端
    int interpreter(const std::string &S);                 // 指令分词 将第一个词存入tmp1 剩余的存入tmp2
}
#pragma once
#include "Stack.hpp"
#include <vector>
#include <string>
#include "CONSTEXPRS.hpp"
class Finance
{
public:
    bool isCost; // 1:支出 0:收入
    db cash;     // 金额
};
namespace BigBrother // 负责日志相关操作
{
    Stack<Finance> &cashLog();                           // 金额变动日志
    int show_finance(const std::vector<std::string> &S); // 指令 财务记录查询
}
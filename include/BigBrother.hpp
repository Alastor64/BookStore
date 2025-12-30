#pragma once
#include "Stack.hpp"
#include <vector>
#include <string>
#include "CONSTEXPRS.hpp"
#include "User.hpp"
#include "Book.hpp"
#include <iomanip>
class Finance // 单次资金变动
{
public:
    bool isCost; // 1:支出 0:收入
    db cash;     // 金额
};
class Log
{
public:
    decltype(time(NULL)) T;
};

namespace COMMAND_TYPE
{
    enum COMMAND
    {
        MODIFY = 0,
        BUY,
        IMPORT,
        CREATE,
        ADD,
        DELETE,
        PASSWD,
        COMMAND_COUNT
    };
    const std::string name[COMMAND_COUNT] = {
        "modify",
        "buy",
        "import",
        "create",
        "add",
        "delete",
        "passwd"};
}
class Report
{
public:
    time_t T;
    PRIVILEGE privilege;
    decltype(User::ID) account;
    COMMAND_TYPE::COMMAND operation;
    void headprint();
};
class FinanceReport
{
public:
    decltype(Book::ISBN) book;
    decltype(Book::quantity) deltaQ;
    decltype(Book::price) deltaC;
    void print();
};
namespace BigBrother // 负责日志相关操作
{
    Stack<FinanceReport> &financeLog();
    Stack<Finance> &cashLog();                           // 资金变动日志
    int show_finance(const std::vector<std::string> &S); // 指令 财务记录查询
    std::string PRIVILEGE_name(PRIVILEGE p);
}
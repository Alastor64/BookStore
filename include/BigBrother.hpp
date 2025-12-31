#pragma once
#include <vector>
#include <string>
#include <iomanip>
#include "Book.hpp"
#include "User.hpp"
#include "Stack.hpp"
class Finance // 单次资金变动
{
public:
    bool isCost; // 1:支出 0:收入
    db cash;     // 金额
};

namespace COMMAND_TYPE // 更改数据的操作
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
    const std::string name[COMMAND_COUNT] = { // 更改数据的操作名称
        "modify",
        "buy",
        "import",
        "create",
        "add",
        "delete",
        "passwd"};
}
class Report // 单条日志 时间+操作者+操作
{
public:
    Report() {}
    Report(const Report &tmp);
    time_t T;                        // 时间
    PRIVILEGE privilege;             // 身份
    decltype(User::ID) account;      // 操作者
    COMMAND_TYPE::COMMAND operation; // 操作
    void headprint();                // 输出
};
class FinanceReport : public Report // 单条财务日志
{

public:
    FinanceReport() {}
    FinanceReport(const Report &tmp);
    decltype(Book::ISBN) book;       // 操作对象
    decltype(Book::quantity) deltaQ; // 库存变化绝对值
    decltype(Book::price) deltaC;    // 资金变化绝对值
    void print();                    // 输出
};
class UserReport : public Report // 单条账户变动日志
{
public:
    UserReport() {}
    UserReport(const Report &tmp);
    decltype(User::ID) user;         // 操作对象
    decltype(User::password) passwd; // 修改后的密码/创建时的密码
    void print();                    // 输出
};
class BookReport : public Report // 单条书本信息变动日志
{
public:
    BookReport() {}
    BookReport(const Report &tmp);
    decltype(Book::ISBN) book;  // 操作对象
    BOOK_INFO key;              // 修改的条目
    decltype(Book::ISBN) tmp1;  // ISBN修改结果
    decltype(Book::name) tmp2;  // 书名、作者、关键字修改结果
    decltype(Book::price) tmp3; // 售价修改结果
    void print();               // 输出
};
namespace BigBrother // 负责日志相关操作
{
    Stack<BookReport> &bookLog();                           // 书本信息变动日志
    Stack<UserReport> &userLog();                           // 账户变动日志
    Stack<FinanceReport> &financeLog();                     // 财务日志
    Stack<Finance> &cashLog();                              // 资金变动日志
    int show_finance(const std::vector<std::string> &S);    // 指令 财务记录查询
    std::string PRIVILEGE_name(PRIVILEGE p);                // 权限对应身份名
    int report_finance(const std::vector<std::string> &S);  // 指令 生成财务记录报告
    int report_employee(const std::vector<std::string> &S); // 生成全体员工工作情况
    int log(const std::vector<std::string> &S);             // 生成日志
}
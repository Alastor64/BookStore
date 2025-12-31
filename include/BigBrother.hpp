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
    Report() {}
    Report(const Report &tmp);
    time_t T;
    PRIVILEGE privilege;
    decltype(User::ID) account;
    COMMAND_TYPE::COMMAND operation;
    void headprint();
};
class FinanceReport : public Report
{
private:
    static const std::string unit;

public:
    FinanceReport() {}
    FinanceReport(const Report &tmp);
    decltype(Book::ISBN) book;
    decltype(Book::quantity) deltaQ;
    decltype(Book::price) deltaC;
    void print();
};
class UserReport : public Report
{
public:
    UserReport() {}
    UserReport(const Report &tmp);
    decltype(User::ID) user;
    decltype(User::password) passwd;
    void print();
};
class BookReport : public Report
{
public:
    BookReport() {}
    BookReport(const Report &tmp);
    decltype(Book::ISBN) book;
    BOOK_INFO key;
    decltype(Book::ISBN) tmp1;
    decltype(Book::name) tmp2;
    decltype(Book::price) tmp3;
    void print();
};
namespace BigBrother // 负责日志相关操作
{
    Stack<BookReport> &bookLog();
    Stack<UserReport> &userLog();
    Stack<FinanceReport> &financeLog();
    Stack<Finance> &cashLog();                           // 资金变动日志
    int show_finance(const std::vector<std::string> &S); // 指令 财务记录查询
    std::string PRIVILEGE_name(PRIVILEGE p);
    int report_finance(const std::vector<std::string> &S);
    int report_employee(const std::vector<std::string> &S);
    int log(const std::vector<std::string> &S);
}
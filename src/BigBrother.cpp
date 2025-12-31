#include "BigBrother.hpp"
#include "Stack.hpp"
#include "MyTypedef.hpp"
#include "Name.hpp"
#include "MyTypedef.hpp"
const std::string REPORT_SPLIT = " "; //"║";表格列分隔符

namespace BigBrother
{
    std::vector<Finance> tmp;
    std::vector<FinanceReport> tmpFr;
    std::vector<UserReport> tmpUr;
    std::vector<BookReport> tmpBr;
    void print(int &i, int &j, int &k);
}
int BigBrother::show_finance(const std::vector<std::string> &S)
{
    if (S.size() > 2)
        return -1;
    ll count;
    if (S.size() == 1)
        count = cashLog().size();
    else if (NAME::to_int(S.at(1), count))
        return 1;
    if (count < 0 || count > cashLog().size())
        return 2;
    if (!count && S.size() == 2)
    {
        std::cout << std::endl;
        return 0;
    }
    db gain = 0.0, cost = 0.0;
    cashLog().top(count, tmp);
    for (int i = 0; i < tmp.size(); i++)
        if (tmp.at(i).isCost)
            cost += tmp.at(i).cash;
        else
            gain += tmp.at(i).cash;
    std::cout << "+ " << gain << " - " << cost << std::endl;
    return 0;
}
std::string BigBrother::PRIVILEGE_name(PRIVILEGE p)
{
    if (p == PRIVILEGE::VISITOR)
        return "Null";
    if (p == PRIVILEGE::GUEST)
        return "Guest";
    if (p == PRIVILEGE::STAFF)
        return "Staff";
    if (p == PRIVILEGE::BOSS)
        return "Boss";
    if (p == PRIVILEGE::BIG_BROTHER)
        return "Auto";
    return "Error";
}
void Report::headprint()
{
    tm local = *localtime(&T);
    std::cout << '[' << std::right << std::setfill('0')
              << std::setw(4) << local.tm_year + 1900 << '.'
              << std::setw(2) << local.tm_mon + 1 << '.'
              << std::setw(2) << local.tm_mday << ' '
              << std::setw(2) << local.tm_hour << ':'
              << std::setw(2) << local.tm_min << ':'
              << std::setw(2) << local.tm_sec << "]" << REPORT_SPLIT
              << std::left << std::setfill(' ')
              << std::setw(5) << BigBrother::PRIVILEGE_name(privilege) << ' ';
    account.print(account.max_size());
    std::cout << REPORT_SPLIT << std::setw(6) << COMMAND_TYPE::name[operation] << REPORT_SPLIT;
}

const std::string FinanceReport::unit = "￥";

FinanceReport::FinanceReport(const Report &tmp) : Report(tmp) {}
void FinanceReport::print()
{
    this->headprint();
    book.print(account.max_size());
    std::cout << REPORT_SPLIT;
    std::cout << std::right << std::setfill('0');
    if (operation == COMMAND_TYPE::BUY)
        std::cout << '-';
    else
        std::cout << '+';
    std::cout << std::setw(10) << deltaQ;
    std::cout << REPORT_SPLIT;
    if (operation == COMMAND_TYPE::BUY)
        std::cout << '+';
    else
        std::cout << '-';
    std::cout << std::setw(24) << deltaC << unit;
    std::cout << REPORT_SPLIT;
}

int BigBrother::report_finance(const std::vector<std::string> &S)
{
    if (S.size() != 1)
        return -1;
    financeLog().top(financeLog().size(), tmpFr);
    for (int i = 0; i < tmpFr.size(); i++)
    {
        tmpFr.at(i).print();
        std::cout << std::endl;
    }
    return 0;
}
void UserReport::print()
{
    this->headprint();
    user.print(user.max_size());
    std::cout << REPORT_SPLIT;
    if (operation == COMMAND_TYPE::PASSWD || operation == COMMAND_TYPE::ADD)
    {
        passwd.print(passwd.max_size());
        std::cout << REPORT_SPLIT;
    }
}
void BookReport::print()
{
    this->headprint();
    book.print(account.max_size());
    std::cout << REPORT_SPLIT;
    if (operation == COMMAND_TYPE::CREATE)
        return;
    std::cout << std::setw(7) << BOOK_KEYS[static_cast<int>(key)];
    std::cout << std::setw(REPORT_SPLIT.length()) << "=";
    if (key == BOOK_INFO::ISBN)
        tmp1.print(tmp1.max_size());
    else if (key == BOOK_INFO::PRICE)
        std::cout << std::setw(13) << tmp3;
    else
        tmp2.print(tmp2.max_size());
    std::cout << REPORT_SPLIT;
}
Report::Report(const Report &tmp)
{
    account = tmp.account;
    privilege = tmp.privilege;
    operation = tmp.operation;
    T = tmp.T;
}

UserReport::UserReport(const Report &tmp) : Report(tmp) {}

BookReport::BookReport(const Report &tmp) : Report(tmp) {}

int BigBrother::report_employee(const std::vector<std::string> &S)
{
    if (S.size() != 1)
        return -1;
    financeLog().top(financeLog().size(), tmpFr);
    userLog().top(userLog().size(), tmpUr);
    bookLog().top(bookLog().size(), tmpBr);
    int i = 0, j = 0, k = 0;
    while (i < tmpFr.size() || j < tmpUr.size() || k < tmpBr.size())
    {
        if (i < tmpFr.size() && tmpFr.at(i).privilege < PRIVILEGE::STAFF)
        {
            i++;
            continue;
        }
        if (j < tmpUr.size() && tmpUr.at(j).privilege < PRIVILEGE::STAFF)
        {
            j++;
            continue;
        }
        if (k < tmpUr.size() && tmpUr.at(k).privilege < PRIVILEGE::STAFF)
        {
            k++;
            continue;
        }
        print(i, j, k);
        std::cout << std::endl;
    }
    return 0;
}
int BigBrother::log(const std::vector<std::string> &S)
{
    if (S.size() != 0)
        return -1;
    financeLog().top(financeLog().size(), tmpFr);
    userLog().top(userLog().size(), tmpUr);
    bookLog().top(bookLog().size(), tmpBr);
    int i = 0, j = 0, k = 0;
    while (i < tmpFr.size() || j < tmpUr.size() || k < tmpBr.size())
    {
        print(i, j, k);
        std::cout << std::endl;
    }
    return 0;
}
void BigBrother::print(int &i, int &j, int &k)
{
    time_t t1, t2, t3;
    t1 = t2 = t3 = time(NULL);
    if (i < tmpFr.size())
        t1 = tmpFr.at(i).T;
    if (j < tmpUr.size())
        t2 = tmpUr.at(j).T;
    if (k < tmpBr.size())
        t3 = tmpBr.at(k).T;
    if (t1 <= t2 && t1 <= t3)
    {
        tmpFr.at(i).print();
        i++;
        return;
    }
    if (t2 <= t1 && t2 <= t3)
    {
        tmpUr.at(j).print();
        j++;
        return;
    }
    if (t3 <= t1 && t3 <= t2)
    {
        tmpBr.at(k).print();
        k++;
        return;
    }
}
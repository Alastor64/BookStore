#include "BigBrother.hpp"
#include "Name.hpp"
#include "CONSTEXPRS.hpp"
namespace BigBrother
{
    std::vector<Finance> tmp;
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
              << std::setw(2) << local.tm_sec << "] "
              << std::left << std::setfill(' ')
              << std::setw(5) << BigBrother::PRIVILEGE_name(privilege) << ' ';
    account.print(account.max_size());
    std::cout << ' ' << std::setw(6) << COMMAND_TYPE::name[operation] << ' ';
}
void FinanceReport::print()
{
    this->print();
    book.print(book.max_size());
    std::cout << ' ';
    if (deltaQ >= 0)
        std::cout << '+' << std::setw(10);
    else
        std::cout << std::setw(11);
    std::cout << deltaQ;
    std::cout << " ";
    std::cout << std::right << std::setfill('0');
    if (deltaC >= 0.00000000000000L)
        std::cout << '+' << std::setw(24);
    else
        std::cout << std::setw(25);
    std::cout << deltaC;
    std::cout << std::endl;
}
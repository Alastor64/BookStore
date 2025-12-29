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
#pragma once
#include "Stack.hpp"
#include <vector>
#include <string>
#include "CONSTEXPRS.hpp"
class Finance
{
public:
    bool isCost;
    db cash;
};
namespace BigBrother
{
    Stack<Finance> &cashLog();
    int show_finance(const std::vector<std::string> &S);
}
#pragma once
#include "Stack.hpp"
#include <vector>
#include <string>
class Finance
{
public:
    bool isCost;
    double cash;
};
namespace BigBrother
{
    Stack<Finance> &cashLog();
    int show_finance(const std::vector<std::string> &S);
}
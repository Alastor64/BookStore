#pragma once
#include "UserManager.hpp"
namespace Commander
{
    typedef std::string::const_iterator it;
    int excute(const std::string &inPut, std::string &outPut);
    int scanfString(it &L, it &R, std::string &S, const it &end);
    int exit(const std::vector<std::string> &S);
    int receptionist();
}
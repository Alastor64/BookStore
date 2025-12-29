#include "Name.hpp"
#include "CONSTEXPRS.hpp"
bool NAME::numLetter(char c)
{
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
}
bool NAME::visible(char c)
{
    return (c > ' ' && c < 127);
}
bool NAME::common(char c)
{
    return visible(c) && (c != '\"' && c != '\"');
}
bool NAME::command(char c)
{
    return visible(c) || c == SPLIT_CHAR;
}
int NAME::to_int(const std::string &S, ll &an)
{
    if (S.length() > 10)
        return -1;
    int _ = 0, i = 0;
    an = 0;
    if (S.at(0) == '-')
    {
        _ = 1;
        i++;
    }
    if (i >= S.length())
        return 1;
    for (; i < S.length(); i++)
    {
        if (S.at(i) < '0' || S.at(i) > '9')
            return 2;
        an = (an << 1) + (an << 3);
        an += S.at(i) & 15;
    }
    if (abs(an) > INT32_MAX)
        return 3;
    if (_)
        an = -an;
    return 0;
}
int NAME::to_real(const std::string &S, db &an)
{
    if (S.length() > 13)
        return -1;
    int _ = 0, i = 0;
    int SU = 0, MI = 0, fg = 0;
    if (S.at(0) == '-')
    {
        _ = 1;
        i++;
    }
    if (S.at(i) == '.')
        return 6;
    if (i >= S.length())
        return 1;
    for (; i < S.length(); i++)
    {
        if (S.at(i) == '.')
        {
            if (fg)
                return 2;
            else
                fg = 1;
            MI = 1;
            continue;
        }
        if (S.at(i) < '0' || S.at(i) > '9')
            return 3;
        SU = (SU << 1) + (SU << 3);
        MI = (MI << 1) + (MI << 3);
        SU += S.at(i) & 15;
    }
    if (S.back() == '.')
        return 5;
    if (MI == 1)
        return 4;
    if (!MI)
        MI = 1;
    if (_)
        an = -SU / db(MI);
    else
        an = SU / db(MI);
    return 0;
}

int NAME::is_positive_real(const std::string &S)
{
    if (S.length() > 13)
        return 0;
    int fg = 0, pos = 0;
    for (int i = 0; i < S.length(); i++)
    {
        if (S.at(i) == '.')
            if (fg)
                return 0;
            else
                fg = 1;
        else if (S.at(i) < '0' || S.at(i) > '9')
            return 0;
        else if (S.at(i) > '0')
            pos = 1;
    }
    if (S.back() == '.')
        return 0;
    if (S.front() == '.')
        return 0;
    return pos;
}
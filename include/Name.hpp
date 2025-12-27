#pragma once
#include <array>
#include <string>
#include <math.h>
#include <string>
enum class NAME_TYPE
{
    NUM_LETTER, // 数字，字母，下划线
    VISIBLE,    // 除不可见字符以外 ASCII 字符
    COMMON,     // 除不可见字符和英文双引号以外 ASCII 字符
    COMMAND,
};
namespace NAME
{
    bool numLetter(char c); // 数字，字母，下划线;
    bool visible(char c);   // 除不可见字符以外 ASCII 字符;
    bool common(char c);    // 除不可见字符和英文双引号以外 ASCII 字符
    bool command(char c);
    int to_int(const std::string &S, int &an);
    int to_real(const std::string &S, double &an);
    int is_positive_real(const std::string &S);
}
template <int size, NAME_TYPE T>
class Name : public std::array<char, size> // 未测试
{

public:
    int length;
    Name()
    {
        length = 0;
        for (int i = 0; i < size; i++)
            this->at(i) = '\0';
    }
    Name(const std::string &s)
    {
        if (!check(s))
            return;
        length = s.length();
        for (int i = 0; i < length; i++)
            this->at(i) = s[i];
        for (int i = length; i < size; i++)
            this->at(i) = '\0';
    }
    static bool check(const std::string &s) // 检查字符合法性
    {
        if (s.length() > size)
            return 0;
        bool fg = 1;
        for (int i = 0; i < s.length(); i++)
        {
            if (T == NAME_TYPE::NUM_LETTER)
                fg &= NAME::numLetter(s[i]);
            if (T == NAME_TYPE::VISIBLE)
                fg &= NAME::visible(s[i]);
            if (T == NAME_TYPE::COMMON)
                fg &= NAME::common(s[i]);
            if (T == NAME_TYPE::COMMAND)
                fg &= NAME::command(s[i]);
        }
        return fg;
    }
    void pusk_back(char c)
    {
        this->at(length++) = c;
    }
    void print()
    {
        for (int i = 0; i < length; i++)
            printf("%c", this->at(i));
    }
};

template <int size, NAME_TYPE T>
bool operator>(const Name<size, T> &a, const Name<size, T> &b)
{
    for (int i = 0; i < std::min(a.length, b.length); i++)
    {
        if (a.at(i) > b.at(i))
            return 1;
        if (a.at(i) < b.at(i))
            return 0;
    }
    return a.length > b.length;
}

template <int size, NAME_TYPE T>
bool operator<(const Name<size, T> &a, const Name<size, T> &b)
{
    return b > a;
}
template <int size, NAME_TYPE T>
bool operator!=(const Name<size, T> &a, const Name<size, T> &b)
{
    if (a.length != b.length)
        return 1;
    for (int i = 0; i < a.length; i++)
        if (a.at(i) != b.at(i))
            return 1;
    return 0;
}
template <int size, NAME_TYPE T>
bool operator==(const Name<size, T> &a, const Name<size, T> &b)
{
    return !(a != b);
}
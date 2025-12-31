#pragma once
#include <array>
#include <string>
#include <cmath>
#include <string>
#include <iostream>
#include <cstdint>
#include "MyTypedef.hpp"
enum class NAME_TYPE // 合法字符类型
{
    NUM_LETTER, // 数字，字母，下划线
    VISIBLE,    // 除不可见字符以外 ASCII 字符
    COMMON,     // 除不可见字符和英文双引号以外 ASCII 字符
};
namespace NAME
{
    bool numLetter(char c);                     // 数字，字母，下划线;
    bool visible(char c);                       // 除不可见字符以外 ASCII 字符;
    bool common(char c);                        // 除不可见字符和英文双引号以外 ASCII 字符
    int to_int(const std::string &S, ll &an);   // 转换为非负整数
    int to_real(const std::string &S, db &an);  // 转换为非负实数
    int is_positive_real(const std::string &S); // 判断是否为非负实数
}
template <int size, NAME_TYPE T>
class Name : public std::array<char, size> // 合法字符串类
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
        }
        return fg;
    }
    void pusk_back(char c) // 添加一个字符，超过上限会RE
    {
        this->at(length++) = c;
    }
    void print(int w = 0, char f = ' ') const // 输出，左对齐
    {
        for (int i = 0; i < length; i++)
            std::cout << this->at(i);
        for (int i = length; i < w; i++)
            std::cout << f;
    }
    bool empty() const // 是否为空串
    {
        return !length;
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
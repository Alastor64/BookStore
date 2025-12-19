#pragma once
#include <array>
#include <string>
namespace NAME // 未测试
{
    enum NAME_TYPE
    {
        NUM_LETTER, // 数字，字母，下划线
        VISIBLE,    // 除不可见字符以外 ASCII 字符
        COMMON,     // 除不可见字符和英文双引号以外 ASCII 字符
    };
    bool numLetter(char c) // 数字，字母，下划线
    {
        return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
    }
    bool visible(char c) // 除不可见字符以外 ASCII 字符
    {
        return (c > ' ' && c < 127);
    }
    bool common(char c) // 除不可见字符和英文双引号以外 ASCII 字符
    {
        return (c > ' ' && c < 127) && (c != '\"' && c != '\"');
    }
}
template <int size, NAME::NAME_TYPE T>
class Name : std::array<char, size> // 未测试
{

public:
    int length;
    Name()
    {
        length = 0;
    }
    Name(const std::string &s)
    {
        if (!check(s))
            return;
        length = s.length();
        for (int i = 0; i < length; i++)
            this->at(i) = s[i];
    }
    static bool check(const std::string &s) // 检查字符合法性
    {
        if (s.length() > size)
            return 0;
        bool fg = 1;
        for (int i = 0; i < s.length(); i++)
        {
            if (T == NAME::NUM_LETTER)
                fg &= NAME::numLetter(s[i]);
            if (T == NAME::VISIBLE)
                fg &= NAME::visible(s[i]);
            if (T == NAME::COMMON)
                fg &= NAME::common(s[i]);
        }
        return fg;
    }
    void print()
    {
        for (int i = 0; i < length; i++)
            printf("%c", this->at(i));
    }
};
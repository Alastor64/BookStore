#pragma once
#include "Name.hpp"
#include "Base.hpp"
#include <string>
class Book : public Base // 书本信息
{
public:
    Book() {}                             // 这是个空函数
    Book(const std::string &_ISBN);       // 仅有ISBN，其他条目均为空
    void init(const std::string &_ISBN);  // 设置ISBN，清空其他条目
    Name<20, NAME_TYPE::VISIBLE> ISBN;    // ISBN
    Name<60, NAME_TYPE::COMMON> name;     // 书名
    Name<60, NAME_TYPE::COMMON> author;   // 作者
    Name<60, NAME_TYPE::COMMON> keywords; // 关键字
    ll quantity;                          // 库存
    db price;                             // 售价
};
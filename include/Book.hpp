#pragma once
#include "Name.hpp"
#include "Base.hpp"
#include <string>
constexpr char KEYWORDS_SPLIT_CHAR = '|';           // 关键字分隔符
const std::array<std::string, 5> BOOK_KEYS =        // 与BOOK_INFO对应
    {"ISBN", "name", "author", "keyword", "price"}; //
constexpr bool NEED_QUOTE[] = {0, 1, 1, 1, 0};      // value是否需加引号
enum class BOOK_INFO                                // 部分书本信息条目
{
    ISBN,    // ISBN
    NAME,    // 书名
    AUTHOR,  // 作者
    KEYWORD, // 关键字
    PRICE,   // 售价
};
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
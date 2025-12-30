#pragma
#include "Book.hpp"
#include "UserManager.hpp"
constexpr char KEYWORDS_SPLIT_CHAR = '|';                // 关键字分隔符
const std::array<std::string, 5> BOOK_KEYS =             // 与BOOK_INFO对应
    {"-ISBN", "-name", "-author", "-keyword", "-price"}; //
constexpr bool NEED_QUOTE[] = {0, 1, 1, 1, 0};           // value是否需加引号
enum class BOOK_INFO                                     // 部分书本信息条目
{
    ISBN,    // ISBN
    NAME,    // 书名
    AUTHOR,  // 作者
    KEYWORD, // 关键字
    PRICE,   // 售价
};
namespace BookManager // 负责图书相关操作
{
    IO<Book, 0> &books();                                    // 记录所有Book类，记index为每个Book类在其中的索引
    Map<decltype(Book::ISBN)> &mapISBN();                    // 有序对（IBSN，index）
    Map<decltype(Book::author)> &mapAuthor();                // 有序对（作者，index）
    Map<decltype(Book::name)> &mapName();                    // 有序对（书名，index）
    Map<decltype(Book::keywords)> &mapKeywords();            // 有序对（单个关键字，index）
    int split(const decltype(Book::keywords) &S);            // 从关键字中拆分出单个关键字至变量keywords,若关键字为空不报错
    int addK(int index);                                     // 添加（keywords[]，index）
    int delK(int index);                                     // 删除（keywords[]，index）
    int select(const std::vector<std::string> &S);           // 指令 选择图书
    int buy(const std::vector<std::string> &S, db &Gain);    // 指令 购买图书 收入金额存入Gain
    int import(const std::vector<std::string> &S, db &Cost); // 指令 图书进货 支出金额存入Cost
    int modify(const std::vector<std::string> &S);           // 指令 修改图书信息
    int splitKeys(const std::string &S, int &which);         // 解析" -[key]=[value] " 将[key]在BOOK_INFO中对应的值（int）存入which，将[value]存入value
    int insert(const Book &B, int Index);                    // 插入书本信息对应的有序对
    int eraze(const Book &B, int Index);                     // 删除书本信息对应的有序对
    int show(const std::vector<std::string> &S);             // 指令 检索图书
    int sortByISBN();                                        // 将变量tmpIndex中的index按对应的ISBN排序（升序）
}
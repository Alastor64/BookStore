#pragma
#include "Book.hpp"
#include "UserManager.hpp"
constexpr char KEYWORDS_SPLIT_CHAR = '|';
const std::array<std::string, 5> BOOK_KEYS = {"-ISBN", "-name", "-author", "-keyword", "-price"};
constexpr bool NEED_QUOTE[] = {0, 1, 1, 1, 0};
enum class BOOK_INFO
{
    ISBN,
    NAME,
    AUTHOR,
    KEYWORD,
    PRICE
};
namespace BookManager
{
    IO<Book, 0> &books();
    Map<decltype(Book::ISBN)> &mapISBN();
    Map<decltype(Book::author)> &mapAuthor();
    Map<decltype(Book::name)> &mapName();
    Map<decltype(Book::keywords)> &mapKeywords();
    int split(const decltype(Book::keywords) &S);
    int addK(int index);
    int delK(int index);
    int select(const std::vector<std::string> &S);
    int buy(const std::vector<std::string> &S);
    int import(const std::vector<std::string> &S, double &cost);
    int modify(const std::vector<std::string> &S);
    int splitKeys(const std::string &S, int &which);
    int insert(const Book &B, int Index);
    int eraze(const Book &B, int Index);
    int show(const std::vector<std::string> &S);
    int sortByISBN();
}
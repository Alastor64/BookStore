#pragma
#include "Book.hpp"
#include "UserManager.hpp"
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
}
#include "Book.hpp"
Book::Book(const std::string &_ISBN)
{
    this->init(_ISBN);
}
void Book::init(const std::string &_ISBN)
{
    ISBN = _ISBN;
    name = std::string("");
    author = std::string("");
    keywords = std::string("");
    quantity = 0;
    price = 0.0;
}
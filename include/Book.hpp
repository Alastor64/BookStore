#pragma once
#include "Name.hpp"
#include "Base.hpp"
#include <string>
// class BookISBN : public Name<20, NAME_TYPE::VISIBLE>
// {
// public:
//     BookISBN() : Name<20, NAME_TYPE::VISIBLE>() {}
//     BookISBN(const std::string &s) : Name<20, NAME_TYPE::VISIBLE>(s) {}
// };
// class BookName : public Name<60, NAME_TYPE::COMMON>
// {
// public:
//     BookName() : Name<60, NAME_TYPE::COMMON>() {}
//     BookName(const std::string &s) : Name<60, NAME_TYPE::COMMON>(s) {}
// };
// class BookAuthor : public Name<60, NAME_TYPE::COMMON>
// {
// public:
//     BookAuthor() : Name<60, NAME_TYPE::COMMON>() {}
//     BookAuthor(const std::string &s) : Name<60, NAME_TYPE::COMMON>(s) {}
// };
// class BookKeywords : public Name<60, NAME_TYPE::COMMON>
// {
// public:
//     BookKeywords() : Name<60, NAME_TYPE::COMMON>() {}
//     BookKeywords(const std::string &s) : Name<60, NAME_TYPE::COMMON>(s) {}
// };
class Book : public Base
{
public:
    Book() {}
    Book(const std::string &_ISBN);
    void init(const std::string &_ISBN);
    Name<20, NAME_TYPE::VISIBLE> ISBN;
    Name<60, NAME_TYPE::COMMON> name;
    Name<60, NAME_TYPE::COMMON> author;
    Name<60, NAME_TYPE::COMMON> keywords;
    ll quantity;
    db price;
};
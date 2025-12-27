#pragma once
#include "Name.hpp"
#include "Base.hpp"
#include <string>
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
    int quantity;
    double price;
};
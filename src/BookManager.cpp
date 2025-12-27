#include "BookManager.hpp"
namespace BookManager
{
    Book tmp;
    std::vector<decltype(Book::keywords)> keywords;
}
int BookManager::split(const decltype(Book::keywords) &S)
{
    keywords.clear();
    keywords.push_back(std::string(""));
    for (int i = 0; i < S.length; i++)
    {
        if (S.at(i) != KEYWORDS_SPLIT_CHAR)
        {
            keywords.back().pusk_back(S.at(i));
        }
        else
        {
            if (!keywords.back().length)
                return 1;
            keywords.push_back(std::string(""));
        }
    }
    if (!keywords.back().length)
        return 1;
    return 0;
}
int BookManager::addK(int index)
{
    for (int i = 0; i < keywords.size(); i++)
    {
        mapKeywords().insert(std::make_pair(keywords.at(i), index));
    }
    return 0;
}
int BookManager::delK(int index)
{
    for (int i = 0; i < keywords.size(); i++)
    {
        mapKeywords().eraze(std::make_pair(keywords.at(i), index));
    }
    return 0;
}
int BookManager::select(const std::vector<std::string> &S)
{
    if (S.size() != 1)
        return -1;
    if (!tmp.ISBN.check(S.at(0)))
        return 1;
    tmp.init(S.at(0));
    int index = mapISBN().show(tmp.ISBN);
    if (index == END_INT)
    {
        index = books().Write(&tmp);
        mapISBN().insert(std::make_pair(tmp.ISBN, index));
    }
    UserManager::selectedBooks().top() = index;
    UserManager::selectedBooks().update();
    return 0;
}
int BookManager::buy(const std::vector<std::string> &S)
{
    if (S.size() != 2)
        return -1;
    if (!tmp.ISBN.check(S.at(0)))
        return 1;
    tmp.ISBN = S.at(0);
    int index = mapISBN().show(tmp.ISBN);
    if (index == END_INT)
        return 2;
    books().Read(&tmp, index);
    int num;
    if (NAME::to_int(S.at(1), num))
        return 3;
    if (num <= 0)
        return 4;
    if (num > tmp.quantity)
        return 5;
    tmp.quantity -= num;
    books().Update(&tmp, index);
    return 0;
}
int BookManager::import(const std::vector<std::string> &S, double &cost)
{
    if (S.size() != 2)
        return -1;
    int index = UserManager::getBook();
    if (index == END_INT)
        return 1;
    int num;
    if (NAME::to_int(S.at(0), num))
        return 2;
    if (num <= 0)
        return 3;
    if (!NAME::is_positive_real(S.at(1)))
        return 4;
    books().Read(&tmp, index);
    tmp.quantity += num;
    books().Update(&tmp, index);
    NAME::to_real(S.at(1), cost);
    return 0;
}
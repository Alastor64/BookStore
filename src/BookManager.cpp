#include "BookManager.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
namespace BookManager
{
    Book tmp, tmp2;
    std::vector<decltype(Book::keywords)> keywords;
    std::string key;
    std::string value;
    bool flag[BOOK_KEYS.max_size()];
    std::vector<int> tmpIndex;
    std::vector<std::pair<decltype(Book::ISBN), int>> tmpSort;
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
            if (keywords.back().empty())
                return 1;
            keywords.push_back(std::string(""));
        }
    }
    if (keywords.back().empty())
        return 1;
    // std::cout << keywords.size() << std::endl; // #
    std::sort(keywords.begin(), keywords.end());
    for (int i = 1; i < keywords.size(); i++)
        if (keywords.at(i - 1) == keywords.at(i))
            return 2;
    return 0;
}
int BookManager::addK(int index)
{
    // std::cout << keywords.size() << std::endl; // #
    for (int i = 0; i < keywords.size(); i++)
    {
        // std::cout << "fuck\n"; // #
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
int BookManager::buy(const std::vector<std::string> &S, double &Gain)
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
    ll num;
    if (NAME::to_int(S.at(1), num))
        return 3;
    if (num <= 0)
        return 4;
    if (num > tmp.quantity)
        return 5;
    tmp.quantity -= num;
    books().Update(&tmp, index);
    Gain = num * tmp.price;
    std::cout << Gain << std::endl;
    return 0;
}
int BookManager::import(const std::vector<std::string> &S, double &cost)
{
    if (S.size() != 2)
        return -1;
    int index = UserManager::getBook();
    if (index == END_INT)
        return 1;
    ll num;
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
int BookManager::insert(const Book &B, int Index) // 确保keywords已经更新
{
    mapISBN().insert(std::make_pair(B.ISBN, Index));
    if (!B.name.empty())
        mapName().insert(std::make_pair(B.name, Index));
    if (!B.author.empty())
        mapAuthor().insert(std::make_pair(B.author, Index));
    if (!B.keywords.empty())
        addK(Index);
    return 0;
}
int BookManager::eraze(const Book &B, int Index) // 确保keywords已经更新
{
    mapISBN().eraze(std::make_pair(B.ISBN, Index));
    if (!B.name.empty())
        mapName().eraze(std::make_pair(B.name, Index));
    if (!B.author.empty())
        mapAuthor().eraze(std::make_pair(B.author, Index));
    if (!B.keywords.empty())
        delK(Index);
    return 0;
}
int BookManager::splitKeys(const std::string &S, int &which)
{
    typedef std::string::const_iterator it;
    it L = S.begin(), R;
    while (L != S.end() && *L != '=')
        L++;
    if (L == S.end())
        return 1;
    key.assign(S.begin(), L);
    L++;
    which = -1;
    for (int j = 0; j < BOOK_KEYS.max_size(); j++)
    {
        if (key == BOOK_KEYS.at(j))
            which = j;
    }
    if (which == -1)
        return 2;
    if (flag[which])
        return 3;
    R = S.end();
    if (NEED_QUOTE[which])
    {
        if (L == S.end())
            return 4;
        if (*L != '\"')
            return 5;
        R--;
        if (L == R)
            return 6;
        if (*R != '\"')
            return 7;
        L++;
    }
    value.assign(L, R);
    return 0;
}
int BookManager::modify(const std::vector<std::string> &S)
{
    if (S.empty())
        return -1;
    int index = UserManager::getBook();
    if (index == END_INT)
        return 1;
    books().Read(&tmp, index);
    tmp2 = tmp;
    for (int i = 0; i < BOOK_KEYS.max_size(); i++)
        flag[i] = 0;
    for (int i = 0; i < S.size(); i++)
    {
        int which;
        if (splitKeys(S.at(i), which))
            return 2;
        if (value.empty())
            return 3;
        BOOK_INFO info = static_cast<BOOK_INFO>(which);
        if (info == BOOK_INFO::ISBN)
            if (!tmp.ISBN.check(value))
                return 4;
            else
            {
                tmp.ISBN = value;
                if (mapISBN().show(tmp.ISBN) != END_INT)
                    return 5;
            }
        if (info == BOOK_INFO::NAME)
            if (!tmp.name.check(value))
                return 4;
            else
                tmp.name = value;
        if (info == BOOK_INFO::AUTHOR)
            if (!tmp.author.check(value))
                return 4;
            else
                tmp.author = value;
        if (info == BOOK_INFO::KEYWORD)
            if (!tmp.keywords.check(value))
                return 4;
            else
                tmp.keywords = value;
        if (info == BOOK_INFO::PRICE)
            if (NAME::to_real(value, tmp.price))
                return 4;
        flag[which] = 1;
    }
    if (flag[static_cast<int>(BOOK_INFO::KEYWORD)] && split(tmp.keywords))
        return 6;
    split(tmp2.keywords);
    eraze(tmp2, index);
    split(tmp.keywords);
    insert(tmp, index);
    books().Update(&tmp, index);
    return 0;
}
int BookManager::show(const std::vector<std::string> &S)
{
    if (S.size() > 1)
        return -1;
    if (S.empty())
        mapISBN().load(tmpIndex);
    else
    {
        int which;
        for (int i = 0; i < BOOK_KEYS.max_size(); i++)
            flag[i] = 0;
        if (splitKeys(S.at(0), which))
        {
            // printf(":%d\n", splitKeys(S.at(0), which)); // #
            return 1;
        }
        BOOK_INFO info = static_cast<BOOK_INFO>(which);
        if (info == BOOK_INFO::PRICE)
            return 2;
        if (info == BOOK_INFO::ISBN)
            if (tmp.ISBN.check(value))
                mapISBN().show(value, tmpIndex);
            else
                return 3;
        if (info == BOOK_INFO::NAME)
            if (tmp.name.check(value))
                mapName().show(value, tmpIndex);
            else
                return 3;
        if (info == BOOK_INFO::AUTHOR)
            if (tmp.author.check(value))
                mapAuthor().show(value, tmpIndex);
            else
                return 3;
        if (info == BOOK_INFO::KEYWORD)
            if (tmp.keywords.check(value))
            {
                tmp.keywords = value;
                if (split(tmp.keywords))
                    return 4;
                if (keywords.size() != 1)
                    return 5;
                mapKeywords().show(keywords.at(0), tmpIndex);
            }
            else
                return 3;
    }
    if (tmpIndex.empty())
    {
        std::cout << std::endl;
        return 0;
    }
    sortByISBN();
    for (int i = 0; i < tmpIndex.size(); i++)
    {
        int index = tmpIndex.at(i);
        books().Read(&tmp, index);
        tmp.ISBN.print();
        std::cout << "\t";
        tmp.name.print();
        std::cout << "\t";
        tmp.author.print();
        std::cout << "\t";
        tmp.keywords.print();
        std::cout << "\t";
        // std::cout << std::setprecision(2);
        std::cout << tmp.price;
        std::cout << "\t";
        std::cout << tmp.quantity;
        std::cout << std::endl;
    }
    return 0;
}
int BookManager::sortByISBN()
{
    tmpSort.clear();
    for (int i = 0; i < tmpIndex.size(); i++)
    {
        books().Read(&tmp, tmpIndex.at(i));
        tmpSort.push_back(std::make_pair(tmp.ISBN, tmpIndex.at(i)));
    }
    std::sort(tmpSort.begin(), tmpSort.end());
    for (int i = 0; i < tmpIndex.size(); i++)
        tmpIndex.at(i) = tmpSort.at(i).second;
    return 0;
}
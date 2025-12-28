#include "BookManager.hpp"
namespace BookManager
{
    Book tmp, tmp2;
    std::vector<decltype(Book::keywords)> keywords;
    std::string key;
    std::string value;
    bool flag[BOOK_KEYS.max_size()];
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
int BookManager::insert(Book &B, int Index) // 确保keywords已经更新
{
    mapISBN().insert(std::make_pair(B.ISBN, Index));
    if (!B.name.empty())
        mapName().insert(std::make_pair(B.name, Index));
    if (!B.author.empty())
        mapAuthor().insert(std::make_pair(B.author, Index));
    if (!B.keywords.empty())
        for (int i = 0; i < keywords.size(); i++)
            mapKeywords().insert(std::make_pair(keywords.at(i), Index));
    return 0;
}
int BookManager::eraze(Book &B, int Index) // 确保keywords已经更新
{
    mapISBN().eraze(std::make_pair(B.ISBN, Index));
    if (!B.name.empty())
        mapName().eraze(std::make_pair(B.name, Index));
    if (!B.author.empty())
        mapAuthor().eraze(std::make_pair(B.author, Index));
    if (!B.keywords.empty())
        for (int i = 0; i < keywords.size(); i++)
            mapKeywords().eraze(std::make_pair(keywords.at(i), Index));
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
            if (tmp.ISBN.check(value))
                return 4;
            else
                tmp.ISBN = value;
        if (info == BOOK_INFO::NAME)
            if (tmp.name.check(value))
                return 4;
            else
                tmp.name = value;
        if (info == BOOK_INFO::AUTHOR)
            if (tmp.author.check(value))
                return 4;
            else
                tmp.author = value;
        if (info == BOOK_INFO::KEYWORD)
            if (tmp.keywords.check(value))
                return 4;
            else
                tmp.keywords = value;
        if (info == BOOK_INFO::PRICE)
            if (NAME::to_real(value, tmp.price))
                return 4;
    }
    if (split(tmp.keywords))
        return 5;
    insert(tmp, index);
    eraze(tmp2, index);
    books().Update(&tmp, index);
    return 0;
}
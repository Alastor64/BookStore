#pragma once
#include <array>
#include <string>
#include "Vector.hpp"
#include "CONSTEXPRS.hpp"
template <class T>
class Head
{
public:
    Head() {}
    Head(const T &V, int BS, int I)
    {
        value = V;
        blockSize = BS;
        index = I;
    }
    T value;
    int blockSize;
    int index;
};
template <class T>
class List
{
private:
    typedef std::array<T, MAX_BLOCK_SIZE> Array;
    typedef std::pair<int, int> pii;

protected:
    Array tmp;
    Vector<Head<T>> heads;
    IO<Array, 0> Data;
    int locateArray(const T &Value, int n) // 查找tmp中最后一个小于等于Value的位置,不存在返回END
    {
        int fg = END_INT;
        for (int i = 0; i < n; i++)
            if (tmp.at(i) <= Value)
                fg = i;
        return fg;
    }
    void insertArray(const T &V, int index) // 将V插入tmp，使其下标为index
    {
        for (int i = MAX_BLOCK_SIZE - 1; i > index; i--)
            tmp.at(i) = tmp.at(i - 1);
        tmp.at(index) = V;
    }
    void erazeArray(int index) // 删除下标为index的值
    {
        for (int i = index; i < MAX_BLOCK_SIZE - 1; i++)
            tmp.at(i) = tmp.at(i + 1);
    }

public:
    List(const std::string &FN) : heads(FN + ".heads")
    {
        Data = IO<Array, 0>(FN + ".block");
    }
    pii locate(const T &Value) // 查找最后一个小于等于Value的位置并载入对应块到tmp,不存在返回END
    {
        if (heads.empty() || heads.front().value > Value)
            return END_PII;
        for (int i = 1; i < heads.size(); i++)
        {
            if (heads.at(i).value > Value)
            {
                Data.Read(&tmp, heads.at(i - 1).index);
                int j = locateArray(Value, heads.at(i - 1).blockSize);
                return pii(i - 1, j);
            }
        }
        Data.Read(&tmp, heads.back().index);
        int j = locateArray(Value, heads.back().blockSize);
        return pii(heads.size() - 1, j);
    }
    void insert(const T &Value)
    {
        if (heads.empty())
        {
            tmp.at(0) = Value;
            heads.push_back(Head(tmp.front(), 1, Data.Write(&tmp)));
            heads.update();
            return;
        }
        pii index = locate(Value);
        int i;
        if (index == END_PII)
        {
            i = 0;
            Data.Read(&tmp, heads.front().index);
            insertArray(Value, 0);
        }
        else
        {
            i = index.first;
            insertArray(Value, index.second + 1);
        }
        heads.at(i).value = tmp.front();
        Data.Update(&tmp, heads.at(i).index);
        heads.at(i).blockSize++;
        if (heads.at(i).blockSize >= MAX_BLOCK_SIZE)
        {
            heads.at(i).blockSize = MAX_BLOCK_SIZE >> 1;
            for (int i = 0; i < (MAX_BLOCK_SIZE >> 1); i++)
                tmp.at(i) = tmp.at(i + (MAX_BLOCK_SIZE >> 1));
            heads.insert(heads.begin() + i + 1, Head(tmp.front(), MAX_BLOCK_SIZE >> 1, Data.Write(&tmp)));
        }
        heads.update();
    }
    pii find(const T &Value) // 不存在返回END
    {
        if (heads.empty())
            return END_PII;
        pii index = locate(Value);
        if (index == END_PII)
            return END_PII;
        if (tmp.at(index.second) == Value)
            return index;
        else
            return END_PII;
    }
    void eraze(const T &Value)
    {
        pii index = find(Value);
        if (index != END_PII)
        {
            erazeArray(index.second);
            heads.at(index.first).blockSize--;
            if (heads.at(index.first).blockSize > 0)
            {
                heads.at(index.first).value = tmp.front();
                Data.Update(&tmp, heads.at(index.first).index);
            }
            else
            {
                Data.Delete(heads.at(index.first).index);
                heads.erase(heads.begin() + index.first);
            }
            heads.update();
        }
    }
};
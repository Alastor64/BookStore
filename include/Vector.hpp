#pragma once
#include "IO.hpp"
#include <vector>
#include <string>
#include <cstdio>
#include <cmath>
template <class T>
class Vector : public std::vector<T> // 动态数组
{
protected:
    IO<T, 1> Data;

public:
    Vector(const std::string &FN)
    {
        Data = IO<T, 1>(FN, 1);
        this->clear();
        int n = Data.Get_info(0);
        if (n)
        {
            T tmp;
            for (int i = 0; i < n; i++)
            {
                Data.Read(&tmp, Data.frontIndex() + i * sizeof(T));
                this->push_back(tmp);
            }
        }
    }

    void update() // WARNING 时间复杂度O(size) !!!
    {
        int N = Data.fileSize;
        if (N < this->size())
            Data.Write(&this->at(N), this->size() - N);
        Data.Write_info(this->size(), 0);
        Data.Update(&this->front(), Data.frontIndex(), std::min(N, int(this->size())));
    }
};
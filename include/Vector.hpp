#pragma once
#include "IO.hpp"
#include <vector>
#include <string>
#include <stdio.h>
#include <math.h>
template <class T>
class Vector : public std::vector<T>
{
protected:
    const std::string filename;
    IO<T, 1> *Data() // return IO<T, 1>::instance(filename);
    {
        return IO<T, 1>::instance(filename);
    }

public:
    Vector(const std::string &FN) : filename(FN) // reload and then initialize if failed 未测试
    {
        this->clear();
        int n = Data()->Get_info(0);
        if (n)
        {
            T tmp;
            for (int i = 0; i < n; i++)
            {
                // printf("i:%d\n", i);#
                Data()->Read(&tmp, Data()->frontIndex() + i * sizeof(T));
                this->push_back(tmp);
            }
        }
    }

    void update() // WARNING time comsumption O(size) !!! 但是文件操作O(1)
    {
        int N = Data()->fileSize;
        if (N < this->size())
            Data()->Write(&this->at(N), this->size() - N);
        Data()->Write_info(this->size(), 0);
        Data()->Update(&this->front(), Data()->frontIndex(), std::min(N, int(this->size())));
    }
};
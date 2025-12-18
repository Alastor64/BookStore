#pragma once
#include "IO.hpp"
#include <vector>
#include <string>
using std::string;
template <class T>
class Vector : public std::vector<T> // 未测试
{
protected:
    const string filename;
    IO<T, 1> *Data() // return IO<T, 1>::instance(filename);
    {
        return IO<T, 1>::instance(filename);
    }

public:
    Vector(const string &FN) : filename(FN) // reload and then initialize if failed 未测试
    {
        this->clear();
        int n = Data()->Get_info(0);
        if (n)
        {
            T tmp;
            for (int i = 0; i < n; i++)
            {
                Data()->Read(&tmp, Data()->frontIndex() + i * sizeof(T));
                this->push_back(tmp);
            }
        }
    }

    void update() // WARNING time comsumption O(size) !!! 未测试
    {
        Data()->initialise();
        Data()->Write_info(this->size(), 0);
        for (int i = 0; i < this->size(); i++)
        {
            Data()->Write(&this->at(i));
        }
    }
};
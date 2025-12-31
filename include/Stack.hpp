#pragma once
#include "IO.hpp"
#include <string>
#include <vector>
template <class T>
class Stack // 未测试
{
protected:
    T topElement;  // 栈顶元素
    int n;         // 栈中元素数量
    IO<T, 1> Data; // return IO_base<T, 1>::instance(filename);
    int topIndex() // 栈顶索引
    {
        return Data.frontIndex() + (n - 1) * sizeof(T);
    }

public:
    Stack(const std::string &FN) // 仅读取栈顶，空栈不读取
    {
        Data = IO<T, 1>(FN, 1);
        n = Data.Get_info(0);
        if (n)
            Data.Read(&topElement, topIndex());
    }
    T &top() // 栈顶引用 空栈是未定义行为
    {
        return topElement;
    }
    int top(int m, std::vector<T> &an) // T()必须存在
    {
        if (m > n)
            return -1;
        if (!m)
        {
            an.clear();
            return 0;
        }
        an.assign(m, T());
        Data.Read(&an.front(), topIndex() - (m - 1) * sizeof(T), m);
        return 0;
    }
    void push(const T &tmp) // 会先更新原栈顶，在压入、更新新栈顶
    {
        if (n)
            update();
        n++;
        topElement = tmp;
        Data.Write_info(n, 0);
        if (n > Data.fileSize)
            Data.Write(&topElement);
        else
            Data.Update(&topElement, topIndex());
    }
    void clear() // 清空
    {
        n = 0;
        Data.Write_info(n, 0);
    }
    void pop() // 空栈是未定义行为
    {
        n--;
        Data.Write_info(n, 0);
        if (n)
            Data.Read(&topElement, topIndex());
    }
    void update() // 空栈是未定义行为
    {
        Data.Update(&topElement, topIndex());
    }
    bool empty() // 判断是否为空
    {
        return !n;
    }
    int size() // 返回大小
    {
        return n;
    }
};
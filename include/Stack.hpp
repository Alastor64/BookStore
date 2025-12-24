#pragma once
#include "IO.hpp"
#include <string>
template <class T>
class Stack // 未测试
{
protected:
    std::string filename;
    T topElement;
    int n;           // 栈中元素数量
    int fileSize;    // 当前数据文件能容纳元素数量
    IO<T, 2> *Data() // return IO_base<T, 1>::instance(filename);
    {
        return IO<T, 2>::instance(filename);
    }
    int topIndex() // 栈顶索引
    {
        return Data()->frontIndex() + (n - 1) * sizeof(T);
    }

public:
    Stack(const std::string &FN) : filename(FN) // 仅读取栈顶，空栈不读取
    {
        n = Data()->Get_info(0);
        fileSize = Data()->Get_info(1);
        if (n)
            Data()->Read(&topElement, topIndex());
    }
    T &top() // 栈顶引用 空栈是未定义行为
    {
        return topElement;
    }
    void push(const T &tmp) // 会先更新原栈顶，在压入、更新新栈顶
    {
        update();
        n++;
        topElement = tmp;
        Data()->Write_info(n, 0);
        if (n > fileSize)
        {
            fileSize++;
            Data()->Write_info(fileSize, 1);
            Data()->Write(&topElement);
        }
        else
            Data()->Update(&tmp, topIndex());
    }
    void pop() // 空栈会直接return
    {
        if (empty())
            return;
        n--;
        Data()->Write_info(n, 0);
        Data()->Read(&topElement, topIndex());
    }
    void update() // 空栈是未定义行为
    {
        Data()->Update(&topElement, Data()->frontIndex() + (n - 1) * sizeof(T));
    }
    bool empty()
    {
        return !n;
    }
    int size()
    {
        return n;
    }
};
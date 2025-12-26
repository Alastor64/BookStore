#pragma once
#include "IO.hpp"
#include "CONSTEXPRS.hpp"
#include <iostream>
class Base // 未测试
{
protected:
    virtual IO_base *Data() = 0; // WARNING nullptr runtime error!

public:
    int THIS;
    Base() {}
    void assign(int _THIS)
    {
        THIS = _THIS;
        if (_THIS != END_INT)
            read();
    }
    void write() // 将自己插入文件
    {
        THIS = Data()->Peep();
        Data()->Write(this);
    }
    void update() // 用自己更新文件
    {
        printf("za");
        Data();
        printf("%d\n", THIS);
        Data()->Update(this, THIS);
        printf("zz\n");
    }
    void read() // 从文件读取自己
    {
        Data()->Read(this, THIS);
    }
    void Delete() // 将自己从文件中删除 未测试
    {
        Data()->Delete(THIS);
    }
};
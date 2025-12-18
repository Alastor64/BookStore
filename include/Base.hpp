#pragma once
#include "IO.hpp"
class Base // 未测试
{
protected:
    virtual IO_base *Data() = 0; // WARNING nullptr runtime error!

public:
    int THIS;
    void write() // 将自己插入文件
    {
        THIS = Data()->Peep();
        Data()->Write(this);
    }
    void updata() // 用自己更新文件
    {
        Data()->Update(this, THIS);
    }
    void read() // 从文件读取自己
    {
        Data()->Read(this, THIS);
    }
};
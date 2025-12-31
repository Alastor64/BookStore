#pragma once
#include <string>
#include <cassert>
#include "MyTypedef.hpp"
#include <iostream>
const std::string DATA_PATH = std::string("./data/"); // 磁盘数据存储目录
class IO_base                                         // 文件读写基类
{

protected:
    FILE *file;                                                                   // tmp
    std::string file_name;                                                        // 路径+文件名
    int info_len;                                                                 // 存储的int数量
    int extra_info;                                                               // 额外存储的int数量 默认额外int值为0
    virtual int sizeofT() = 0;                                                    // 存储类字节数
    int last;                                                                     //= -1;最后一个被delete的位置距文件头的偏移量
    int back;                                                                     //= info_len * sizeof(int);文件字节数
    void updateinfo();                                                            // 更新必要info信息last和back
    std::string format(const std::string &FN);                                    // 文件名格式化（加上路径和扩展名）
    IO_base();                                                                    // 默认文件名为空 extra_info=0
    IO_base(int extra_info);                                                      // 默认文件名为空
    IO_base(const std::string &filename, int extra_info = 0, bool NEED_INIT = 0); // 默认extra_info=0 NEED_INIT=0

public:
    int fileSize;                                                   // 文件当前能存储类的最大数量
    int reload(const std::string &FN = "");                         // 读取名为FN的文件并绑定，留空则读取原绑定文件
    void initialise(const std::string &FN = "");                    // 初始化名为FN的文件并绑定，留空则初始化原绑定文件
    int Get_info(int n);                                            // 返回第n个额外存储的int（0-base）
    void Write_info(int tmp, int n);                                // 更新第n个额外存储的int（0-base）
    int Peep();                                                     // 返回下一个插入索引 未测试
    int Write(const void *t, const int num = 1);                    // 添加num个类（WARNING num!=1仅适用于不使用Delete的实例）
    void Update(const void *t, const int index, const int num = 1); // 更新num个类（WARNING num!=1仅适用于不使用Delete的实例）
    void Read(void *t, const int index, const int num = 1);         // 读取num个类（WARNING num!=1仅适用于不使用Delete的实例）
    void Delete(const int index);                                   // 删除一个类
    int frontIndex();                                               // 类存储起始索引
    IO_base &operator=(const IO_base &tmp);
};

template <class T, int EXTRA_INFO = 0>
class IO : public IO_base // 文件读写类
{
protected:
    int sizeofT() override
    {
        return sizeof(T);
    }

public:
    IO() : IO_base(EXTRA_INFO) {}
    IO(const std::string &filename, bool NEED_INIT = 0) : IO_base(filename, EXTRA_INFO, NEED_INIT) {}
    static IO<T, EXTRA_INFO> &instance(const std::string &className)
    {
        static IO<T, EXTRA_INFO> Instance(className, 1);
        return Instance;
    }
};

template <class T, int EXTRA_INFO = 2>
class MemoryRiver : public IO_base // 仅用于提交测试正确性
{
protected:
    int sizeofT() override
    {
        return sizeof(T);
    }

public:
    MemoryRiver() : IO_base(EXTRA_INFO) {}
    MemoryRiver(const std::string &filename) : IO_base(filename, EXTRA_INFO) {}
    void get_info(int &tmp, int n)
    {
        tmp = this->Get_info(n - 1);
    }
    void write_info(int tmp, int n)
    {
        this->Write_info(tmp, n - 1);
    }
    int write(const T &t)
    {
        return this->Write(&t);
    }
    void update(T &t, const int index)
    {
        this->Update((void *)&t, index);
    }
    void read(T &t, const int index)
    {
        this->Read((void *)&t, index);
    }
};
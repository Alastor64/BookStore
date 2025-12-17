#pragma once
#include <string>
#include <assert.h>
using std::string;
class IO_base
{
protected:
    FILE *file;
    string file_name;
    int info_len;
    int extra_info;
    virtual int sizeofT() = 0;
    int last;                //= -1;最后一个被delete的位置距文件头的偏移量
    int back;                //= info_len * sizeof(int);文件字节数
    void updateinfo();       // 更新必要info信息last和back
    IO_base();               // 默认文件名为空 extra_info=0
    IO_base(int extra_info); // 默认文件名为空
    IO_base(const string &filename, int extra_info = 0, bool NEED_INIT = 0);

public:
    int reload(const string &FN = "");      // 读取名为FN的文件并绑定，留空则读取原绑定文件
    void initialise(const string &FN = ""); // 初始化名为FN的文件并绑定，留空则初始化原绑定文件
    int Get_info(int n);
    void Write_info(int tmp, int n);
    int Peep(); // 返回下一个插入索引 未测试
    int Write(const void *t);
    void Update(void *t, const int index);
    void Read(void *t, const int index);
    void Delete(const int index); // 未测试
    int frontIndex();             // 类存储起始索引 未测试
    int backIndex();              // 类存储截止索引 未测试
};

template <class T, int EXTRA_INFO = 0>
class IO : public IO_base
{
protected:
    int sizeofT() override
    {
        return sizeof(T);
    }

public:
    IO() : IO_base(EXTRA_INFO) {}
    IO(const string &filename, bool NEED_INIT = 0) : IO_base(filename, EXTRA_INFO, NEED_INIT) {}
    static IO<T, EXTRA_INFO> *instance(const string &className)
    {
        static IO<T, EXTRA_INFO> Instance(className + ".data", 1); // WARNING!
        return &Instance;
    }
};

template <class T, int EXTRA_INFO = 2>
class MemoryRiver : public IO_base
{
protected:
    int sizeofT() override
    {
        return sizeof(T);
    }

public:
    MemoryRiver() : IO_base(EXTRA_INFO) {}
    MemoryRiver(const string &filename) : IO_base(filename, EXTRA_INFO) {}
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
#pragma
#include <string>
#include <assert.h>
using std::string;
template <int extra_info = 0>
class IO_base
{
protected:
    FILE *file;
    string file_name;
    int info_len;
    virtual int sizeofT() = 0;
    int last; //= -1;最后一个被delete的位置距文件头的偏移量
    int back; //= info_len * sizeof(int);文件字节数
    void updateinfo()
    {
        file = fopen(file_name.c_str(), "rb+");
        assert(file && "updateinfo failed"[0]);
        fseek(file, 0, SEEK_SET);
        fwrite(&last, sizeof(int), 1, file);
        fwrite(&back, sizeof(int), 1, file);
        fclose(file);
    }

public:
    IO_base()
    {
        info_len = 2 + extra_info;
    }
    IO_base(const string &filename) : file_name("./data/" + filename)
    {
        info_len = 2 + extra_info;
    }
    int reload(string FN = "")
    {
        if (FN != "")
            file_name = FN;
        file = fopen(file_name.c_str(), "rb+");
        if (file)
        {
            fread(&last, sizeof(int), 1, file);
            fread(&back, sizeof(int), 1, file);
            fclose(file);
            return 1;
        }
        return 0;
    }
    void initialise(string FN = "")
    {
        if (FN != "")
            file_name = "./data/" + FN;
        file = fopen(file_name.c_str(), "wb");
        int tmp = 0;
        for (int i = 0; i < info_len; i++)
        {
            fwrite(&tmp, sizeof(int), 1, file);
        }
        fclose(file);
        last = -1;
        back = info_len * sizeof(int);
        updateinfo();
    }
    void Get_info(int &tmp, int n)
    {
        if (n >= extra_info)
            return;
        file = fopen(file_name.c_str(), "rb+");
        fseek(file, (n + 2) * sizeof(int), SEEK_SET);
        fread(&tmp, sizeof(int), 1, file);
        fclose(file);
    }
    void Write_info(int tmp, int n)
    {
        if (n >= extra_info)
            return;
        file = fopen(file_name.c_str(), "rb+");
        fseek(file, (n + 2) * sizeof(int), SEEK_SET);
        fwrite(&tmp, sizeof(int), 1, file);
        fclose(file);
    }
    int Write(const void *t)
    {
        int R;
        if (last == -1)
        {
            file = fopen(file_name.c_str(), "ab");
            assert(file && ("write failed")[0]);
            fwrite(t, sizeofT(), 1, file);
            fclose(file);
            R = back;
            back += sizeofT();
        }
        else
        {
            R = last;
            file = fopen(file_name.c_str(), "rb+");
            assert(file && ("write failed")[0]);
            fseek(file, R, SEEK_SET);
            fread(&last, sizeof(int), 1, file);
            fseek(file, R, SEEK_SET);
            fwrite(t, sizeofT(), 1, file);
            fclose(file);
        }
        updateinfo();
        return R;
    }

    void Update(void *t, const int index)
    {
        assert(index < back && index >= info_len && "illegal index");
        file = fopen(file_name.c_str(), "rb+");
        assert(file && ("update failed")[0]);
        fseek(file, index, SEEK_SET);
        fwrite(t, sizeofT(), 1, file);
        fclose(file);
        updateinfo();
    }

    void Read(void *t, const int index)
    {
        assert(index < back && index >= info_len && "illegal index");
        file = fopen(file_name.c_str(), "rb+");
        assert(file && ("read failed")[0]);
        fseek(file, index, SEEK_SET);
        fread(t, sizeofT(), 1, file);
        fclose(file);
        updateinfo();
    }
    void Delete(const int index) // 未测试
    {
        assert(index < back && index >= info_len && "illegal index");
        file = fopen(file_name.c_str(), "rb+");
        assert(file && ("delete failed")[0]);
        fseek(file, index, SEEK_SET);
        fwrite(&last, sizeof(int), 1, file);
        fclose(file);
        last = index;
        updateinfo();
    }
};

template <class T, int extra_info = 0>
class IO : public IO_base<extra_info>
{
protected:
    int sizeofT() override
    {
        return sizeof(T);
    }

public:
    IO() : IO_base<extra_info>()
    {
    }
    IO(const string &filename) : IO_base<extra_info>(filename)
    {
    }
    static IO<T> *instance()
    {
        static IO<T> Instance(T::className + ".data"); // WARNING!
        return &Instance;
    }
};

template <class T, int extra_info = 2>
class MemoryRiver : public IO_base<extra_info>
{
protected:
    int sizeofT() override
    {
        return sizeof(T);
    }

public:
    MemoryRiver() : IO_base<extra_info>()
    {
    }
    MemoryRiver(const string &filename) : IO_base<extra_info>(filename)
    {
    }
    void get_info(int &tmp, int n)
    {
        this->Get_info(tmp, n - 1);
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
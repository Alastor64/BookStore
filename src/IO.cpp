#include "IO.hpp"
// protected

void IO_base::updateinfo()
{
    file = fopen(file_name.c_str(), "rb+");
    assert(file && "updateinfo failed");
    fseek(file, 0, SEEK_SET);
    fwrite(&last, sizeof(int), 1, file);
    fwrite(&back, sizeof(int), 1, file);
    fwrite(&fileSize, sizeof(int), 1, file);
    fclose(file);
}

std::string IO_base::format(const std::string &FN)
{
    return DATA_PATH + FN + ".data";
}

IO_base::IO_base() : IO_base(0) {}

IO_base::IO_base(int EXTRA_INFO)
{
    extra_info = EXTRA_INFO;
    info_len = 3 + EXTRA_INFO;
}

IO_base::IO_base(const std::string &FN, int EXTRA_INFO, bool NEED_INIT) : IO_base(EXTRA_INFO)
{
    file_name = format(FN);
    if (NEED_INIT)
    {
        if (!reload())
            initialise();
    }
}

// public

IO_base &IO_base::operator=(const IO_base &tmp)
{
    fileSize = tmp.fileSize;
    last = tmp.last;
    back = tmp.back;
    file_name = tmp.file_name;
    return *this;
}
int IO_base::reload(const std::string &FN)
{
    if (FN != "")
        file_name = format(FN);
    file = fopen(file_name.c_str(), "rb+");
    if (file)
    {
        fread(&last, sizeof(int), 1, file);
        fread(&back, sizeof(int), 1, file);
        fread(&fileSize, sizeof(int), 1, file);
        fclose(file);
        return 1;
    }
    return 0;
}

void IO_base::initialise(const std::string &FN)
{
    if (FN != "")
        file_name = format(FN);
    file = fopen(file_name.c_str(), "wb");
    int tmp = 0;
    for (int i = 0; i < info_len; i++)
    {
        fwrite(&tmp, sizeof(int), 1, file);
    }
    fclose(file);
    last = -1;
    back = info_len * sizeof(int);
    fileSize = 0;
    updateinfo();
}

int IO_base::Get_info(int n)
{
    if (n >= extra_info)
        return 0;
    int tmp;
    file = fopen(file_name.c_str(), "rb+");
    fseek(file, (n + info_len - extra_info) * sizeof(int), SEEK_SET);
    fread(&tmp, sizeof(int), 1, file);
    fclose(file);
    return tmp;
}

void IO_base::Write_info(int tmp, int n)
{
    if (n >= extra_info)
        return;
    file = fopen(file_name.c_str(), "rb+");
    fseek(file, (n + info_len - extra_info) * sizeof(int), SEEK_SET);
    fwrite(&tmp, sizeof(int), 1, file);
    fclose(file);
}

int IO_base::Peep()
{
    if (last == -1)
        return back;
    else
        return last;
}

int IO_base::Write(const void *t, const int num)
{
    int R;
    if (last == -1)
    {
        file = fopen(file_name.c_str(), "ab");
        assert(file && "write failed");
        if (!file)
        {
            std::cout << file_name << std::endl;
            std::exit(0);
        }
        fwrite(t, sizeofT(), num, file);
        fileSize += num;
        fclose(file);
        R = back;
        back += sizeofT();
    }
    else
    {
        R = last;
        file = fopen(file_name.c_str(), "rb+");
        if (!file)
        {
            std::cout << file_name << std::endl;
            std::exit(0);
        }
        fseek(file, R, SEEK_SET);
        fread(&last, sizeof(int), 1, file);
        fseek(file, R, SEEK_SET);
        fwrite(t, sizeofT(), num, file);
        fclose(file);
    }
    updateinfo();
    return R;
}

void IO_base::Update(const void *t, const int index, const int num)
{
    assert(index < back && index >= frontIndex() && "illegal index");
    file = fopen(file_name.c_str(), "rb+");
    assert(file && ("update failed")[0]);
    fseek(file, index, SEEK_SET);
    fwrite(t, sizeofT(), num, file);
    fclose(file);
    updateinfo();
}

void IO_base::Read(void *t, const int index, const int num)
{
    assert(index < back && index >= frontIndex() && "illegal index");
    file = fopen(file_name.c_str(), "rb+");
    assert(file && ("read failed")[0]);
    fseek(file, index, SEEK_SET);
    fread(t, sizeofT(), num, file);
    fclose(file);
    updateinfo();
}

void IO_base::Delete(const int index)
{
    assert(index < back && index >= frontIndex() && "illegal index");
    file = fopen(file_name.c_str(), "rb+");
    assert(file && ("delete failed")[0]);
    fseek(file, index, SEEK_SET);
    fwrite(&last, sizeof(int), 1, file);
    fclose(file);
    last = index;
    updateinfo();
}

int IO_base::frontIndex()
{
    return info_len * sizeof(int);
}
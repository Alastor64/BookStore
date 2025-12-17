#include "IO.hpp"
// protected

void IO_base::updateinfo()
{
    file = fopen(file_name.c_str(), "rb+");
    assert(file && "updateinfo failed"[0]);
    fseek(file, 0, SEEK_SET);
    fwrite(&last, sizeof(int), 1, file);
    fwrite(&back, sizeof(int), 1, file);
    fclose(file);
}

// public
IO_base::IO_base(int extra_info = 0)
{
    info_len = 2 + extra_info;
}

IO_base::IO_base(const string &filename, int extra_info = 0) : file_name("./data/" + filename)
{
    info_len = 2 + extra_info;
}

int IO_base::reload(string FN = "")
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

void IO_base::initialise(string FN = "")
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

void IO_base::Get_info(int &tmp, int n)
{
    if (n >= extra_info)
        return;
    file = fopen(file_name.c_str(), "rb+");
    fseek(file, (n + 2) * sizeof(int), SEEK_SET);
    fread(&tmp, sizeof(int), 1, file);
    fclose(file);
}

void IO_base::Write_info(int tmp, int n)
{
    if (n >= extra_info)
        return;
    file = fopen(file_name.c_str(), "rb+");
    fseek(file, (n + 2) * sizeof(int), SEEK_SET);
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

int IO_base::Write(const void *t)
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

void IO_base::Update(void *t, const int index)
{
    assert(index < back && index >= info_len && "illegal index");
    file = fopen(file_name.c_str(), "rb+");
    assert(file && ("update failed")[0]);
    fseek(file, index, SEEK_SET);
    fwrite(t, sizeofT(), 1, file);
    fclose(file);
    updateinfo();
}

void IO_base::Read(void *t, const int index)
{
    assert(index < back && index >= info_len && "illegal index");
    file = fopen(file_name.c_str(), "rb+");
    assert(file && ("read failed")[0]);
    fseek(file, index, SEEK_SET);
    fread(t, sizeofT(), 1, file);
    fclose(file);
    updateinfo();
}

void IO_base::Delete(const int index)
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
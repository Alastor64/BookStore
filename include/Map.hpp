#pragma once
#include "List.hpp"
#include "CONSTEXPRS.hpp"
#include <vector>
#include <cstdint>
template <class K>
class Map : public List<std::pair<K, int>>
{
private:
    typedef std::pair<K, int> pKi;
    typedef std::pair<int, int> pii;

public:
    Map(const std::string &FN) : List<pKi>(FN) {}
    void load(std::vector<int> &Ans)
    {
        Ans.clear();
        for (int i = 0; i < this->heads.size(); i++)
        {
            this->Data.Read(&this->tmp, this->heads.at(i).index);
            for (int j = 0; j < this->heads.at(i).blockSize; j++)
                Ans.push_back(this->tmp.at(j).second);
        }
    }
    void show(const K &Key, std::vector<int> &Ans) // 将Ans清空，然后将键值为Key的value存入Ans
    {
        Ans.clear();
        if (this->heads.empty())
            return;
        pii hd = this->locate(pKi(Key, -1));
        if (hd == END_PII)
            hd = pii(0, -1);
        int j = hd.second + 1;
        bool fg = 1;
        for (int i = hd.first; fg && i < this->heads.size(); i++, j = 0)
        {
            this->Data.Read(&this->tmp, this->heads.at(i).index);
            for (; j < this->heads.at(i).blockSize; j++)
                if (this->tmp.at(j).first != Key)
                {
                    fg = 0;
                    break;
                }
                else
                    Ans.push_back(this->tmp.at(j).second);
        }
    }
    int show(const K &Key) // 返回键值为Key的最大index，不存在返回END
    {
        if (this->heads.empty())
            return END_INT;
        int j = this->locate(pKi(Key, INT32_MAX)).second;
        if (j == END_INT)
            return END_INT;
        else if (this->tmp.at(j).first == Key)
            return this->tmp.at(j).second;
        else
            return END_INT;
    }
};
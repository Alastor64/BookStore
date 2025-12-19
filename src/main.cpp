#include "IO.hpp"
#include <iostream>
#include <string>
#include <filesystem>
#include <stdio.h>
#include "Initializer.hpp"
#include "Vector.hpp"
#include "Name.hpp"
int main()
{
    Init();
    char ss[100];
    std::cin.getline(ss, 100);
    std::string S(ss);
    Name<20, NAME::COMMON> A;
    // if (A.check(S))
    A = S;
    A.print();
    Vector<int> s("abab");

    s.pop_back();
    s.push_back(2);
    s.push_back(4);
    s.push_back(6);
    s.pop_back();
    s.update();
    Vector<int> t("abab");
    for (int i = 0; i < t.size(); i++)
    {
        printf("%d ", t.at(i));
    }
    printf("\n");
    // std::string s = std::filesystem::canonical("/proc/self/exe").parent_path().string() + "/data";
    fopen("./data/test", "w");
    IO<int> a("data");
    a.initialise();
    int b = 10;
    int c = a.Write(&b);
    b++;
    int d = a.Write(&b);
    int k;
    a.Read(&k, c);
    printf("%d\n", k);
    a.Read(&k, d);
    printf("%d\n", k);
    // std::cout << std::string(std::filesystem::canonical("/proc/self/exe").parent_path().string());
    return 0;
}
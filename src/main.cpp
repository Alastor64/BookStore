#include "IO.hpp"
#include <iostream>
#include <string>
#include <filesystem>
#include <stdio.h>
#include "Initializer.hpp"
int main()
{
    Init();
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
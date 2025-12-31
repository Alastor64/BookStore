#include "Initializer.hpp"
#include "Map.hpp"
#include "Name.hpp"
#include <string>
#include <iostream>
#include <vector>
#include "UserManager.hpp"
#include "Commander.hpp"
#include <iomanip>
#include "MyTypedef.hpp"
// 以前的调试用的，忽略他们
//  typedef Name<64, NAME_TYPE::VISIBLE> str;
//  std::vector<int> ans;
//  str c;
//  void sol2();
//  void testmapID();
int main()
{
    Init();
    Commander::receptionist();
    return 0;
}
// void testmapID()
// {
//     printf("%d\n", int(sizeof(User)));
//     Name<20, NAME_TYPE::COMMON>
//         SS = std::string("ababab");
//     UserManager::mapID();
//     std::array<int, 20> a;
//     a.size();
//     std::string tmp;
//     std::vector<std::string> V;
//     V.clear();
//     for (int i = 0; i < 4; i++)
//     {
//         std::cin >> tmp;
//         V.push_back(tmp);
//     }
//     std::cout << UserManager::userAdd(V, PRIVILEGE::BIG_BROTHER) << std::endl;
// }
// void sol2()
// {
//     Map<str> mp("DATA");
//     int n, x;
//     scanf("%d", &n);
//     std::string S;
//     while (n--)
//     {
//         std::cin >> S;
//         if (S[0] == 'i')
//         {
//             // printf("I\n");#
//             std::cin >> S;
//             c = S;
//             scanf("%d", &x);
//             mp.insert(std::make_pair(c, x));
//         }
//         else if (S[0] == 'd')
//         {
//             // printf("D\n");#
//             std::cin >> S;
//             c = S;
//             scanf("%d", &x);
//             mp.eraze(std::make_pair(c, x));
//         }
//         else if (S[0] == 'f')
//         {
//             // printf("F\n");#
//             std::cin >> S;
//             c = S;
//             mp.show(c, ans);
//             // printf("oo\n");#
//             if (ans.empty())
//                 printf("null");
//             else
//                 for (int i = 0; i < ans.size(); i++)
//                     printf("%d ", ans.at(i));
//             printf("\n");
//         }
//     }
// }
// Map<int> mp("mapii");
// std::vector<int> kk;
// kk.push_back(1);
// kk.push_back(2);
// kk.push_back(3);
// kk.push_back(4);
// kk.push_back(5);
// kk.insert(kk.begin() + 5, 0);
// for (int i = 0; i < kk.size(); i++)
//     printf("%d ", kk[i]);
// printf("\n");
// // kkk.
// for (int i = 0; i < kkk.max_size(); i++)
//     printf("%d ", kkk[i]);
// printf("\n");

// Head<int> abab;
// List<int> l("bhb");
// // printf("%d\n", l.locate(1).first);
// char ss[100];
// std::cin.getline(ss, 100);
// std::string S(ss);
// Name<20, NAME::COMMON> A;
// // if (A.check(S))
// A = S;
// A.print();
// Vector<int> s("abab");

// s.pop_back();
// s.push_back(2);
// s.push_back(4);
// s.push_back(6);
// s.pop_back();
// s.update();
// Vector<int> t("abab");
// for (int i = 0; i < t.size(); i++)
// {
//     printf("%d ", t.at(i));
// }
// printf("\n");
// // std::string s = std::filesystem::canonical("/proc/self/exe").parent_path().string() + "/data";
// fopen("./data/test", "w");
// IO<int> a("data");
// a.initialise();
// int b = 10;
// int c = a.Write(&b);
// b++;
// int d = a.Write(&b);
// int k;
// a.Read(&k, c);
// printf("%d\n", k);
// a.Read(&k, d);
// printf("%d\n", k);
// // std::cout << std::string(std::filesystem::canonical("/proc/self/exe").parent_path().string());

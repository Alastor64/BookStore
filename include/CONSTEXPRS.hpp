#pragma once
#include <string>
const std::string DATA_PATH = std::string("./data/");                     // 磁盘数据存储目录
constexpr int END_INT = -1;                                               // END
constexpr std::pair<int, int> END_PII = std::pair<int, int>(-1, END_INT); // END
constexpr int MAX_BLOCK_SIZE = 512;                                       // 最大块大小
constexpr int MAX_COMMAND_LENGTH = 500;                                   // 最长可接受指令长度
constexpr char SPLIT_CHAR = ' ';                                          // 指令分词符
const std::string INVALID = std::string("Invalid");                       // 非法反馈输出
typedef long long ll;                                                     // long long
typedef long double db;                                                   // long double